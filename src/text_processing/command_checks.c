#include <stdio.h>
#include <string.h>

#include "command_checks.h"
#include "os_global.h"
#include "text_creation.h"

bool _is_command_exist(const char *cmd) {
  size_t cmd_count = sizeof(help_cmds) / sizeof(help_cmds[0]);
  for (size_t i = 0; i < cmd_count; ++i) {
    if (strcmp(cmd, help_cmds[i].full_name) != 0) {
      if (strcmp(cmd, help_cmds[i].short_name) != 0) {
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
