#ifndef USER_INPUT_PARSER_H
#define USER_INPUT_PARSER_H

#include <stdbool.h>

#include "io.h"
#include "plugin.h"
#include "v_build_global.h"

#define IS_RET_VOID "void"
#define IS_RET_INT "int"
#define IS_RET_bool "bool"
#define IS_RET_CHAR_P "char*"
#define IS_TEXT "text"

#define NO_ARGS "no"

void exec_plugin_command(const char *restrict cmd);

bool is_func_void_no_ret(const plugin_element *elem);

#endif // USER_INPUT_PARSER_H
