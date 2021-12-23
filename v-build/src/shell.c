#include "shell.h"

#include <stdio.h>
#include <string.h>

#include "io.h"
#include "plugin_exec.h"
#include "shell_helper.h"
#include "v_build_global.h"

void run_shell() {
  char *user_input = NULL;

  // must be 1st line. load_io
  load_io();

  RUN_SHELL_LOOP {
    user_input = get_shell_input();

    if (is_help_command(user_input)) {
      exec_help_command(user_input);
    } else if (is_plugin_command(user_input)) {
      try_to_exec_plugin_command(user_input);
    } else {
      print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
    }

    free(user_input);
  }
}
