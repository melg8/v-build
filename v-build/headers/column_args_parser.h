#ifndef COLUMN_ARGS_PARSER_H
#define COLUMN_ARGS_PARSER_H

#include <stdbool.h>

#include "plugin.h"
#include "v_build_global.h"

#define IS_VALUE_VOID "void"
#define IS_VALUE_CHAR_P "char*"
#define IS_VALUE_INT "int"
#define IS_VALUE_BOOL "bool"

#define IS_VALUE_TEXT "text"

#define NO_ARGS "no"

bool get_column_args(const plugin_element *restrict elem);
void parse_etalon_args(const char *elem_args);
bool is_func_has_args(const plugin_element *elem);
void get_user_func_column_args();

// big chank of args checks
bool is_args_ok();
bool is_empty_arg(const char *entered);
bool is_arg_digits(const char *entered);
bool is_entered_arg_is_bool(const char *entered);

bool is_arg_charp(size_t idx);
bool is_arg_int(size_t idx);
bool is_arg_bool(size_t idx);

bool is_func_ret_void(const plugin_element *elem);
bool is_func_ret_int(const plugin_element *elem);
bool is_func_ret_charp(const plugin_element *elem);
bool is_func_ret_bool(const plugin_element *elem);

void reset_user_args();

#endif // COLUMN_ARGS_PARSER_H
