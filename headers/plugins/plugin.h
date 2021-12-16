#ifndef PLUGIN_H
#define PLUGIN_H

#include "plugin_parser.h"
#include "v_build_global.h"

#define P_BEGIN "--begin"
#define P_END "--end"
#define P_NAME "plugin_name = "
#define P_TYPE "type = "
#define P_ALIAS "alias = "
#define P_DIR "dir = "
#define P_EXEC "exec = "
#define P_DESC "desc = "

// plugin struct, see plugins/common.plug for more information
typedef struct plugin {
  char plugin_name[COMMON_TEXT_SIZE];
  char type[COMMON_TEXT_SIZE];
  char alias[COMMON_TEXT_SIZE];
  char dir[COMMON_TEXT_SIZE];
  char exec[COMMON_TEXT_SIZE];
  char desc[COMMON_TEXT_SIZE];
} plugin;

extern plugin plugin_list[PLUGIN_LIST_SIZE];

void load_common_plugin();

void check_common_plugin();

#endif // PLUGIN_H
