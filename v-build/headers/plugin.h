#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdbool.h>

#include "plugin_parser.h"
#include "v_build_global.h"

#define P_BEGIN "--begin"
#define P_END "--end"
#define P_TYPE "type = "
#define P_NAME "name = "
#define P_DIR "dir = "
#define P_EXEC "exec = "
#define P_ARGS "args = "
#define P_DESC "desc = "

// plugin struct, see plugins/common.plug for more information
typedef struct plugin {
  char type[COMMON_TEXT_SIZE];
  char name[COMMON_TEXT_SIZE];
  char dir[COMMON_TEXT_SIZE];
  char exec[COMMON_TEXT_SIZE];
  char args[COMMON_TEXT_SIZE];
  char desc[COMMON_TEXT_SIZE];
} plugin;

extern plugin plugin_list[PLUGIN_LIST_SIZE];

bool is_text_plugin_loaded();

#endif // PLUGIN_H
