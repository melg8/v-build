#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdbool.h>

extern void *plugin_handle;

// 0 if success, -1 if error
int load_plugin(const char *restrict plugin_name);

#endif // PLUGIN_H
