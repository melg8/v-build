#include "shell.h"

#include <stdio.h>
#include <string.h>

#include "bin_exec.h"
#include "column_args_parser.h"
#include "io.h"
#include "line_args_parser.h"
#include "script_exec.h"
#include "shell_helper.h"
#include "v_build_global.h"

void run_shell() {
  // must be 1st line. load i/o library
  load_io();

  set_internal_conf();

  SHELL_LOOP {
    user_input = get_user_input();

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

  unset_internal_conf();
}

void try_to_exec_plugin(const char *user_input) {
  plugin_element *elem = find_element_by_command(user_input);

  if (elem != NULL) {
    run_plugin(elem);
  }

  add_cmd_to_history(user_input, elem);
  reset_user_args();
}

void run_plugin(const plugin_element *elem) {
  bool args_ok = false;
  if (g_conf.is_column_args) {
    args_ok = get_column_args(elem);
  } else if (g_conf.is_line_args) {
    args_ok = fill_line_args(elem);
  }

  if (args_ok) {
    if (is_elem_binary(elem)) {
      exec_bin(elem);
    } else if (is_elem_script(elem)) {
      exec_script(elem);
    }
  }
}
