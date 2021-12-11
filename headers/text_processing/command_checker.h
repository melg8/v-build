#ifndef COMMAND_CHECKER_H
#define COMMAND_CHECKER_H

#include <stddef.h>

#include "os_global.h"

// commands list:

typedef struct cmd_triplet {
  char *full_name;
  char *short_name;
  char *desc;
} cmd_triplet;

static cmd_triplet cmds[SHELL_CMD_COUNT] = {{"help", "h", "help message"}};

int check_command(const char *cmd);

#endif // COMMAND_CHECKER_H
