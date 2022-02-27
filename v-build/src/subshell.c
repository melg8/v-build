#include "subshell.h"

#include <stdio.h>
#include <string.h>

#include "io.h"

bool is_subshell_command(const char *cmd) {
  if (strcmp(cmd, "subshell") == 0) {
    return true;
  }
  return false;
}
