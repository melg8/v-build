#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "os_global.h"
#include "shell.h"
#include "text_processor.h"

void run_shell() {
  CLEAR_SCREEN;

  char *command = NULL;
  RUN_SHELL_LOOP { command = get_command_from_user(); }

  free(command);
}
