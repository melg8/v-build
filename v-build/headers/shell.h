#ifndef SHELL_H
#define SHELL_H

#include "plugin.h"

void run_shell();

// 0 - success, -1 is error
void exec_help_command(const char *cmd);

#endif // SHELL_H
