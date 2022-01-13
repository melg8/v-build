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
  g_conf.is_column_args = true;
  g_conf.is_line_args = false;
}

void run_shell() {
  // must be 1st line. load i/o library
  load_io();

  _set_global_conf();

  char *user_input = NULL;

  SHELL_LOOP {
    user_input = get_shell_input();

    if (is_help_command(user_input)) {
      exec_help_command(user_input);
    } else {
      char *cmd = get_command_from_line(user_input);
      if (is_plugin_command(cmd)) {
        printf("%s\n", cmd);
        break;
        try_to_exec_plugin(cmd);
      } else {
        print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
      }
    }
    free(user_input);
  }
}

void try_to_exec_plugin(const char *user_input) {
  plugin_element *elem = find_element_by_command(user_input);

  if (elem != NULL) {
    // determine the type of command, binary or script
    if (is_elem_binary(elem)) {
      run_binary_command(elem);
    }
  }
}

void run_binary_command(const plugin_element *elem) {
  if (g_conf.is_column_args) {
    get_plugin_args(elem);
  }

  exec_bin(elem);
}
