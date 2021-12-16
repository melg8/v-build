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
#define P_RET_VAL "ret_val ="
#define P_ARGS "args = "
#define P_DESC "desc = "

extern void *plugin_handle;

// plugin struct, see plugins/common.plug for more information
typedef struct plugin {
  char type[COMMON_TEXT_SIZE];
  char name[COMMON_TEXT_SIZE];
  char dir[COMMON_TEXT_SIZE];
  char exec[COMMON_TEXT_SIZE];
  char ret_val[COMMON_TEXT_SIZE];
  char args[COMMON_TEXT_SIZE];
  char desc[COMMON_TEXT_SIZE];
} plugin;

extern plugin plugin_list[PLUGIN_LIST_SIZE];

bool is_text_plugin_loaded();

void_func get_void_func(const plugin *plugin_list, size_t pos);
char_func get_char_func(const plugin *plugin_list, size_t pos);

// basic mandatory functions from libtext
void print_help();
void get_input_from_user();

#endif // PLUGIN_H