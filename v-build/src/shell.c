#include "shell.h"

#include <stdio.h>
#include <string.h>

#include "binary_parser.h"
#include "io.h"
#include "plugin_exec.h"
#include "shell_helper.h"
#include "v_build_global.h"

void run_shell() {
  char *user_input = NULL;

  // must be 1st line. load io library
  load_io();

  RUN_SHELL_LOOP {
    user_input = get_shell_input();

    if (is_help_command(user_input)) {
      exec_help_command(user_input);
    } else if (is_plugin_command(user_input)) {
      // parse user input
      try_to_exec_plugin(user_input);
      // then exec
    } else {
      print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
    }

    free(user_input);
  }
}

void try_to_exec_plugin(const char *user_input) {
  plugin_element *elem = find_element_by_command(user_input);

  // determine the type of command, binary or script
  if (is_elem_binary(elem)) {
    run_binary_command(elem);
  }
}

void run_binary_command(const plugin_element *elem) {
  if (is_user_plugin_input_correct(elem)) {
    exec_plugin(elem);
  }
}
