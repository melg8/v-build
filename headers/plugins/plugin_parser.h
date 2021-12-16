#ifndef PLUGIN_PARSER_H
#define PLUGIN_PARSER_H

#include "plugin.h"
#include "v_build_global.h"

// 0 if success, -1 if error
int load_plugin(const char *restrict plugin_path);

#endif // PLUGIN_PARSER_H
