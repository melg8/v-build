#ifndef USER_INPUT_PARSER_H
#define USER_INPUT_PARSER_H

#include <stdbool.h>

#include "plugin.h"
#include "v_build_global.h"

#define IS_RET_VOID "void"
#define IS_RET_INT "int"
#define IS_RET_BOOL "bool"
#define IS_RET_CHAR_P "char*"
#define IS_TEXT "text"

#define NO_ARGS "no"
#define ARGS_COUNT 10

extern char user_args[ARGS_COUNT][COMMON_TEXT_SIZE];

void exec_plugin_command(const char *restrict cmd);

void *determine_binary_func(const plugin_element *elem,
                            const char *restrict cmd);

void parse_args(const char *user_input);

bool is_func_has_args(const plugin_element *elem);

#endif // USER_INPUT_PARSER_H
