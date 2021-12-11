#include <stdio.h>
#include <string.h>

#include "command_checks.h"

bool _is_command_exist(const char *cmd) {
  for (size_t i = 0; i < SHELL_CMD_COUNT; ++i) {
    if (strcmp(cmd, cmds[i].full_name) != 0) {
      if (strcmp(cmd, cmds[i].short_name) != 0) {
        return false;
      } else {
        return true;
      }
    } else {
      return true;
    }
  }
  return true;
}
