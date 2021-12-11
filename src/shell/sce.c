#include "sce.h"

// SCE - Simple Command Execution

#include <stdio.h>
#include <string.h>

#include "text_processing.h"

void run_sc(const char *cmd) {
  if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0) {
    print_help_msg();
  } else {
    printf("command is simple, but not implemented yet.\n");
  }
}
