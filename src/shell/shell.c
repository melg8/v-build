#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "os_global.h"
#include "shell.h"
#include "text_processing.h"

void run_shell() {
  CLEAR_SCREEN;

  char *command = NULL;
  RUN_SHELL_LOOP {
    command = get_command_from_user();
    if (is_command_exist(command)) {
      // try to exec
    } else {
      error_msg("invalid command, run \"help\" to view list of commands");
    }
  }

  free(command);
}
