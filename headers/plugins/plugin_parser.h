#ifndef PLUGIN_PARSER_H
#define PLUGIN_PARSER_H

#include "os_global.h"

// plugin struct see plugins/common.plug for more information
typedef struct plugin {
  char *name;
  char *dir;
  char *exec;
  char *desc;
} plugin;

static plugin plugin_list[PLUGIN_LIST_SIZE];

#endif // PLUGIN_PARSER_H
