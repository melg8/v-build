#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "os_global.h"
#include "sce.h"
#include "shell.h"
#include "text_processing.h"

void run_shell() {
  RUN_SHELL_LOOP {
    char *command = get_command_from_user(SHELL_TITILE);

    if (is_command_exist(command)) {
      try_to_exec(command);
    } else {
      print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
    }
    free(command);
  }
}

// the command exist in command list
void try_to_exec(const char *command) {
  if (is_command_simple(command)) {
    run_sc(command);
  }
}
