#ifndef SHELL_H
#define SHELL_H

#include "plugin.h"

void run_shell();

void try_to_exec_plugin(const char *restrict user_input);

void run_plugin(const plugin_element *restrict elem);

#endif // SHELL_H
