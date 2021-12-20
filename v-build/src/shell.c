#include "shell.h"

#include "io.h"
#include "shell_helper.h"
#include "v_build_global.h"

void run_shell() {
  // must be 1st line. load_io
  load_io();

  RUN_SHELL_LOOP {
    char *user_input = get_shell_input();

    if (is_help_command_exist(user_input)) {
      exec_help_command(user_input);
    }
    // if (is_plugin_command(user_input) {
    // exec_plugin_command(user_input)
    //}
    else {
      print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
    }
  }
}
