#ifndef PLUGIN_PARSER_H
#define PLUGIN_PARSER_H

#include "v_build_global.h"

// plugin struct see plugins/common.plug for more information
typedef struct plugin {
  char *plugin_name;
  char *alias;
  char *dir;
  char *exec;
  char *desc;
} plugin;

static plugin plugin_list[PLUGIN_LIST_SIZE] = {0};

// 0 - success, -1 - error
int load_plugin(const char *restrict plugin_path);

#endif // PLUGIN_PARSER_H
