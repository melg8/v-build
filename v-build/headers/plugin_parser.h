#ifndef PLUGIN_PARSER_H
#define PLUGIN_PARSER_H

#include "v_build_global.h"

#define P_BEGIN "--begin"
#define P_END "--end"
#define P_TYPE "type = "
#define P_COMMAND "command = "
#define P_EXEC "exec = "
#define P_RET_VAL "ret_val ="
#define P_ARGS "args = "
#define P_DESC "desc = "

#define ELEM_BINARY "bin"
#define ELEM_SCRIPT "script"

// plugin descriptor, see plugins/io.plug for more information
typedef struct plugin_descriptor {
  char type[COMMON_TEXT_SIZE];
  char command[COMMON_TEXT_SIZE];
  char exec[COMMON_TEXT_SIZE];
  char ret_val[COMMON_TEXT_SIZE];
  char args[COMMON_TEXT_SIZE];
  char desc[COMMON_TEXT_SIZE];
} plugin_descriptor;

typedef struct plugin_element {
  char plugin_name[COMMON_TEXT_SIZE];
  plugin_descriptor desc;
} plugin_element;

extern plugin_element list[PLUGIN_LIST_SIZE];

int _load_plugin(const char *restrict plugin_name);
u_int _get_current_pos();

#endif // PLUGIN_PARSER_H
