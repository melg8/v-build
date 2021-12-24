#ifndef BINARY_PARSER_H
#define BINARY_PARSER_H

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
extern size_t _cnt;
extern bool _is_input_correct;
extern bool _is_args_ok;
extern bool _is_has_args;

bool is_user_plugin_input_correct(const plugin_element *restrict elem);

void parse_etalon_args(const char *elem_args);

bool is_func_has_args(const plugin_element *elem);

// 0 success, -1 error
int get_func_args();

// big chank of args checks
bool is_args_ok();
bool is_empty_arg(const char *entered);
bool is_arg_must_be_numeric(const char *expected);
bool is_arg_digits(const char *entered);

void reset_user_args();
void print_incorrect_expected_values(size_t cur_cnt, const char *expected,
                                     const char *entered);

#endif // BINARY_PARSER_H
