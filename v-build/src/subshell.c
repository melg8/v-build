#include "subshell.h"

#include <stdio.h>
#include <string.h>

#include "build_menu.h"
#include "io.h"

static bool is_back_to_shell(const char *user_input) {
  if (strcmp(user_input, "back") == 0) {
    return true;
  }
  return false;
}

bool is_subshell_command(const char *cmd) {
  if (strcmp(cmd, "subshell") == 0) {
    return true;
  }
  return false;
}

void run_subshell() {

  print_info_msg(INFO_MSG, "press \"back\" to move back into shell", YES);
  print_info_msg(INFO_MSG, "press \"build\" for start building", YES);

  SHELL_LOOP {
    user_input = get_user_input(SUBSHELL);

    if (is_help_command(user_input)) {
      exec_help_command(user_input);
    } else if (is_plugin_command(user_input)) {
      try_to_exec_plugin(user_input);
    } else if (is_extra_command(user_input)) {
      exec_extra_command(user_input);
    } else if (is_build_menu(user_input)) {
      run_build_menu();
    } else if (is_back_to_shell(user_input)) {
      break;
    } else {
      print_err();
    }
  }

  free(user_input);
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
