#ifndef PLUGIN_EXEC_H
#define PLUGIN_EXEC_H

#include <stdbool.h>

#include "plugin.h"
#include "user_input_parsing.h"
#include "v_build_global.h"

void try_to_exec_plugin_command(const char *user_input);

#endif // PLUGIN_EXEC_H
