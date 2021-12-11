#include <stdio.h>
#include <string.h>

#include "command_checker.h"

int check_command(const char *cmd) {

  for (size_t i = 0; i < SHELL_CMD_COUNT; ++i) {
    if (cmds[i].full_name == NULL)
      break;

    printf("%s, %s - %s\n", cmds[i].full_name, cmds[i].short_name,
           cmds[i].desc);
  }

  return 0;
}
