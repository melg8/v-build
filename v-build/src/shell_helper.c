#include "shell_helper.h"

#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "io.h"
#include "line_args_parser.h"
#include "plugin.h"
#include "plugin_parser.h"

global_conf g_conf = {0};

pthread_t input_thread;
pthread_t err_thread;
pthread_rwlock_t rwlock;

void *user_input = NULL;

#define PRINT_CONFIG_PARAM(param, param_readable)                              \
  ({                                                                           \
    if (param) {                                                               \
      print_info_msg(CONFIG_NAME(param_readable), GREEN_YES, YES);             \
    } else {                                                                   \
      print_info_msg(CONFIG_NAME(param_readable), RED_NO, YES);                \
    }                                                                          \
  })

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

void set_internal_conf() {
  g_conf.is_column_args = false;
  g_conf.is_line_args = true;

  pthread_rwlock_init(&rwlock, NULL);
}

char *get_user_input() {
  pthread_create(&input_thread, NULL, _thread_input_internal, user_input);
  pthread_join(input_thread, &user_input);
  return ((char *)user_input);
}

static void *_err_func(void *arg) {
  pthread_rwlock_wrlock(&rwlock);
  print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
  pthread_rwlock_unlock(&rwlock);
  pthread_exit(arg);
}

void print_err() {
  pthread_create(&err_thread, NULL, _err_func, NULL);
  pthread_join(err_thread, NULL);
}

void exec_help_command(const char *cmd) {

  if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0) {
    print_help();
  }

  if (strcmp(cmd, "clear") == 0 || strcmp(cmd, "c") == 0) {
    CLEAR_SCREEN;
  }

  if (strcmp(cmd, "show_loaded") == 0 || strcmp(cmd, "sl") == 0) {
    print_loaded_functions();
  }

  if (strcmp(cmd, "plugins_all") == 0 || strcmp(cmd, "pla") == 0) {
    view_all_plugins();
  }

  if (strcmp(cmd, "load") == 0 || strcmp(cmd, "l") == 0) {
    // unused
  }

  if (strcmp(cmd, "set_column_args") == 0 || strcmp(cmd, "sca") == 0) {
    g_conf.is_column_args = true;
    g_conf.is_line_args = false;
    print_info_msg(COMPLETE, "column args", YES);
  }

  if (strcmp(cmd, "set_line_args") == 0 || strcmp(cmd, "sla") == 0) {
    g_conf.is_column_args = false;
    g_conf.is_line_args = true;
    print_info_msg(COMPLETE, "line args", YES);
  }

  if (strcmp(cmd, "view_config") == 0 || strcmp(cmd, "vc") == 0) {
    view_config();
  }

  if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "q") == 0) {
    EXIT(EXIT_SUCCESS);
  }
}

void print_loaded_functions() {
  char name_comparator[COMMON_TEXT_SIZE] = {0};

  for (u_int i = 0; i < get_current_list_pos(); ++i) {
    plugin_element *elem = &list[i];

    //    if (strcmp(elem->plugin_name, "plugins/io.plug") == 0)
    //      continue;

    if (strcmp(name_comparator, elem->plugin_name) != 0) {
      char temp[COMMON_TEXT_SIZE] = {0};
      strcpy(temp, "\n");
      strcat(temp, OS_COLOR_BLUE);
      strcpy(name_comparator, elem->plugin_name);
      strcat(temp, name_comparator);
      strcat(temp, OS_NO_COLOR);
      print_info_msg(temp, ":", YES);

      memset(temp, 0, sizeof(temp));

      strcpy(temp, OS_COLOR_YELLOW);
      print_fmt_msg(0, temp);

      memset(temp, 0, sizeof(temp));
      strcat(temp, "type:");
      print_fmt_msg(8, temp);

      strcpy(temp, "command:");
      print_fmt_msg(30, temp);

      strcpy(temp, "return");
      print_fmt_msg(10, temp);

      strcpy(temp, "args:");
      print_fmt_msg(35, temp);

      strcpy(temp, "description:");
      print_fmt_msg(50, temp);

      strcpy(temp, OS_NO_COLOR);
      strcat(temp, "\n");
      print_msg(temp, 0);
    }

    print_fmt_msg(8, elem->descriptor.type);
    print_fmt_msg(30, elem->descriptor.command);
    print_fmt_msg(10, elem->descriptor.ret_val);
    print_fmt_msg(35, elem->descriptor.args);
    print_fmt_msg(50, elem->descriptor.desc);

    print_msg("\n", 0);
  }
}

void view_all_plugins() {
  DIR *d = opendir("plugins");
  struct dirent *dp = NULL;
  char plugins[COMMON_TEXT_SIZE * 2] = {0};
  strcpy(plugins, "\n");

  if (d == NULL) {
    print_info_msg(ERROR_MSG, strerror(errno), YES);
    return;
  }

  while ((dp = readdir(d)) != 0) {

    if (strstr(dp->d_name, ".plug") != NULL) {
      strcat(plugins, dp->d_name);
      strcat(plugins, "\n");
    }
  }
  strcat(plugins, OS_NO_COLOR);
  print_info_msg(OS_COLOR_YELLOW, plugins, YES);
}

void print_incorrect_expected_values(size_t cur_idx, const char *expected_value,
                                     const char *entered_value) {
  char temp[COMMON_TEXT_SIZE];
  char value[10] = {0};
  strcpy(temp, "arg(");
  sprintf(value, "%lo", cur_idx);
  strcat(temp, value);
  strcat(temp, "), ");
  strcat(temp, "expected type: \"");
  strcat(temp, expected_value);
  strcat(temp, "\", ");
  strcat(temp, "entered value: \"");
  strcat(temp, entered_value);
  strcat(temp, "\"");
  print_info_msg(ERROR_MSG, temp, YES);
}

void view_config() {
  PRINT_CONFIG_PARAM(g_conf.is_column_args, "column args: ");
  PRINT_CONFIG_PARAM(g_conf.is_line_args, "line args: ");
}

bool is_extra_command(const char *cmd) {
  if (strcmp(cmd, "") == 0) {
    return true;
  }

  return false;
}

void exec_extra_command(const char *cmd) {
  if (strcmp(cmd, "") == 0) {
    return;
  }
}

void unset_internal_conf() {
  free(user_input);
  pthread_rwlock_destroy(&rwlock);
}
