#ifndef PLUGIN_PARSER_H
#define PLUGIN_PARSER_H

#include "v_build_global.h"

#define P_BEGIN "--begin"
#define P_END "--end"
#define P_NAME "plugin_name = "
#define P_ALIAS "alias = "
#define P_DIR "dir = "
#define P_EXEC "exec = "
#define P_DESC "desc = "

// plugin struct see plugins/common.plug for more information
typedef struct plugin {
  char plugin_name[COMMON_TEXT_SIZE];
  char alias[COMMON_TEXT_SIZE];
  char dir[COMMON_TEXT_SIZE];
  char exec[COMMON_TEXT_SIZE];
  char desc[COMMON_TEXT_SIZE];
} plugin;

// 0 - success, -1 - error
int load_plugin(const char *restrict plugin_path);

#endif // PLUGIN_PARSER_H
