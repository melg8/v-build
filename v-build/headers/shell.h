#ifndef SHELL_H
#define SHELL_H

#include "io.h"
#include "plugin.h"

void run_shell();
int try_to_load_plugin(const char *restrict plugin_path);

#endif // SHELL_H
