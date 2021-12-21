#ifndef USER_INPUT_PARSER_H
#define USER_INPUT_PARSER_H

#include <stdbool.h>

#include "io.h"
#include "plugin.h"
#include "v_build_global.h"

#define IS_RET_VOID "void"
#define IS_RET_INT "int"
#define IS_RET_BOOL "bool"
#define IS_RET_CHAR_P "char*"
#define IS_TEXT "text"

#define NO_ARGS "no"

void exec_plugin_command(const char *restrict cmd);

void determine_binary_func(const plugin_element *elem,
                           const char *restrict cmd);

// logical parsing functions
bool is_func_no_ret_no_args(const plugin_element *elem);

bool is_func_ret_int_no_args(const plugin_element *elem);
bool is_func_ret_charp_no_args(const plugin_element *elem);
bool is_func_ret_bool_no_args(const plugin_element *elem);

#endif // USER_INPUT_PARSER_H
