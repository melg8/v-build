#include "sce.h"

// SCE - Simple Command Execution

#include <stdio.h>
#include <string.h>

#include "text_processing.h"

static char local_cmd[USER_COMMAND_LEN];

void run_sc(const char *cmd) {
  strcpy(local_cmd, cmd);
  if (is_help()) {
    print_help_msg();
  } else if (is_quit()) {
    EXIT;
  } else if (is_clear()) {
    CLEAR_SCREEN;
  }

  else {
    printf("command is simple, but not implemented yet.\n");
  }
}

bool is_help() {
  return strcmp(local_cmd, "help") == 0 || strcmp(local_cmd, "h") == 0;
}

bool is_quit() {
  return strcmp(local_cmd, "quit") == 0 || strcmp(local_cmd, "q") == 0;
}

bool is_clear() {
  return strcmp(local_cmd, "clear") == 0 || strcmp(local_cmd, "c") == 0;
}
