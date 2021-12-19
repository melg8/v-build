#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "v_build_global.h"

void run_shell() {
  load_io();

  RUN_SHELL_LOOP {
    char *user_input = get_shell_input();

    if (is_command_exist(user_input)) {
      int ret_val = exec_command(user_input);
    } else {
      print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
    }
  }
}

int exec_command(const char *cmd) {
  // exec
  return 0;
}
