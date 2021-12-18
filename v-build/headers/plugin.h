#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdbool.h>

// 0 if success, -1 if error
int load_plugin(const char *restrict plugin_name);

// *cmd if success, NULL if error
void *get_command(const char *restrict command);

int find_command(const char *restrict command);

#endif // PLUGIN_H
