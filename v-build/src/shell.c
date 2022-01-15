#include "shell.h"

#include <pthread.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>

#include "bin_exec.h"
#include "bin_parser.h"
#include "io.h"
#include "line_args_parser.h"
#include "shell_helper.h"
#include "v_build_global.h"

global_conf g_conf = {0};

pthread_t input_thread;
pthread_t err_thread;
pthread_rwlock_t rwlock;

void *user_input = NULL;

static void _set_global_conf() {
  g_conf.is_column_args = false;
  g_conf.is_line_args = true;

  pthread_rwlock_init(&rwlock, NULL);
}

static char *_get_user_command_internal() {

  char *value = NULL;
  if (g_conf.is_line_args) {
    value = get_command_from_line(get_shell_input());
  } else {
    value = get_shell_input();
  }

  return value;
}

static void *_thread_input_internal(void *arg) {
  pthread_rwlock_rdlock(&rwlock);
  arg = ((void *)_get_user_command_internal());
  pthread_rwlock_unlock(&rwlock);
  pthread_exit(arg);
}

static void *err_func(void *arg) {
  pthread_rwlock_wrlock(&rwlock);
  print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
  pthread_rwlock_unlock(&rwlock);
  pthread_exit(arg);
}

static void print_err() {
  pthread_create(&err_thread, NULL, err_func, NULL);
  pthread_join(err_thread, NULL);
}

static char *_get_user_input() {
  pthread_create(&input_thread, NULL, _thread_input_internal, user_input);
  pthread_join(input_thread, &user_input);
  return ((char *)user_input);
}

void run_shell() {
  // must be 1st line. load i/o library
  load_io();

  _set_global_conf();

  SHELL_LOOP {
    user_input = _get_user_input();

    if (is_help_command(user_input)) {
      exec_help_command(user_input);
    } else if (is_plugin_command(user_input)) {
      try_to_exec_plugin(user_input);
    } else if (is_extra_command(user_input)) {
      exec_extra_command(user_input);
    } else {
      print_err();
    }
  }
  free(user_input);

  pthread_rwlock_destroy(&rwlock);
}

void try_to_exec_plugin(const char *user_input) {
  plugin_element *elem = find_element_by_command(user_input);

  if (elem != NULL) {
    // determine the type of command, binary or script
    if (is_elem_binary(elem)) {
      run_binary_command(elem);
    }
  }
  reset_user_args();
}

void run_binary_command(const plugin_element *elem) {
  bool args_ok = false;
  if (g_conf.is_column_args) {
    args_ok = get_plugin_args(elem);
  } else if (g_conf.is_line_args) {
    args_ok = fill_line_args(elem);
  }

  if (args_ok) {
    exec_bin(elem);
  }
}
