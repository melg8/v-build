#ifndef USER_INPUT_PARSING_H
#define USER_INPUT_PARSING_H

#include <stdbool.h>

#include "plugin.h"
#include "v_build_global.h"

#define IS_VALUE_VOID "void"

#define IS_VALUE_INT "int"
#define IS_VALUE_BOOL "bool"
#define IS_VALUE_CHAR_P "char*"

#define IS_VALUE_TEXT "text"

#define NO_ARGS "no"
#define ARGS_COUNT 10

extern char user_args_etalon[ARGS_COUNT][COMMON_TEXT_SIZE];
extern char user_input_args[ARGS_COUNT][COMMON_TEXT_SIZE];
extern size_t cnt;
extern bool is_input_correct;

void parse_user_plugin_input(const char *restrict cmd);
void parse_args(const char *elem_args);

bool is_func_has_args(const plugin_element *elem);
void get_func_args();
bool is_args_ok();

bool is_arg_numeric(const char *arg);

void reset_user_args();

#endif // USER_INPUT_PARSING_H
