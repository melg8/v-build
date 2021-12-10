#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "text_processor.h"

void run_shell() {
  system("clear");

  char *command = NULL;
  command = get_shell_string();

  free(command);
}
