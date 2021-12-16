#ifndef SHELL_H
#define SHELL_H

#include "plugin.h"

void obtain_io();
void try_to_load_plugin(const char *restrict plugin_path);

void run_shell();

#endif // SHELL_H
