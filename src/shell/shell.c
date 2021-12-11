#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "os_global.h"
#include "shell.h"
#include "text_processing.h"

void run_shell() {
  CLEAR_SCREEN;

  RUN_SHELL_LOOP {
    char *command = get_command_from_user();
    if (is_command_exist(command)) {
      print_help_msg();
    } else {
      error_msg(INVALID_COMMAND);
    }
    free(command);
  }
}
