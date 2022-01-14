#include "shell.h"

#include <stdio.h>
#include <string.h>

#include "bin_exec.h"
#include "bin_parser.h"
#include "io.h"
#include "line_args_parser.h"
#include "shell_helper.h"
#include "v_build_global.h"

global_conf g_conf = {0};

static void _set_global_conf() {
  g_conf.is_column_args = false;
  g_conf.is_line_args = true;
}

static char *_get_user_command() {
  if (g_conf.is_line_args) {
    return get_command_from_line(get_shell_input());
  } else {
    return get_shell_input();
  }
}

void run_shell() {
  // must be 1st line. load i/o library
  load_io();

  _set_global_conf();

  char *user_input = NULL;

  SHELL_LOOP {
    user_input = _get_user_command();

    if (is_help_command(user_input)) {
      exec_help_command(user_input);
    } else if (is_plugin_command(user_input)) {
      try_to_exec_plugin(user_input);
    } else if (is_extra_command(user_input)) {
      exec_extra_command(user_input);
    } else {
      print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
    }
  }
  free(user_input);
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
