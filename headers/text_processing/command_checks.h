#ifndef COMMAND_CHECKS_H
#define COMMAND_CHECKS_H

#include <stdbool.h>
#include <stddef.h>

#include "os_global.h"

// commands list:

typedef struct cmd_triplet {
  char *full_name;
  char *short_name;
  char *desc;
} cmd_triplet;

static cmd_triplet cmds[SHELL_CMD_COUNT] = {{"help", "h", "help message"}};

bool _is_command_exist(const char *cmd);

#endif // COMMAND_CHECKS_H
