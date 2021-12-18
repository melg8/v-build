#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdbool.h>

#include "plugin_parser.h"

// 0 if success, -1 if error
int load_plugin(const char *restrict plugin_name);

// *cmd if success, NULL if error
void *get_command(const char *restrict command);

plugin_element *find_command(const char *restrict command);

bool is_command_binary(const plugin_element *restrict elem);

#endif // PLUGIN_H
