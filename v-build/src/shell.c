#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "io.h"
#include "v_build_global.h"

void run_shell() {
  load_io();

  RUN_SHELL_LOOP {
    char *user_input = get_shell_input();

    if (is_help_command_exist(user_input)) {
      int ret_val = exec_help_command(user_input);
    } else {
      print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
    }
  }
}

int exec_help_command(const char *cmd) {

  if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0) {
    print_help();
  }

  return 0;
}
