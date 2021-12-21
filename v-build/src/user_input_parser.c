#include "user_input_parser.h"

#include <stdio.h>
#include <string.h>

void exec_plugin_command(const char *cmd) {
  plugin_element *elem = find_element_by_command(cmd);

  if (elem == NULL) {
    print_info_msg(ERROR_MSG, "Strange behaviour, command not found", YES);
    return;
  }

  if (is_elem_binary(elem)) {

    determine_binary_func(elem, cmd);
  }
}

void determine_binary_func(const plugin_element *elem,
                           const char *restrict cmd) {
  if (is_func_no_ret_no_args(elem)) {
    no_ret_no_args_func f = get_binary_function(cmd);
    f();
  }

  if (is_func_ret_int_no_args(elem)) {
    ret_int_no_args_func f = get_binary_function(cmd);
    int res = f();
    char str[COMMON_TEXT_SIZE] = {0};
    sprintf(str, "%d", res);
    print_info_msg(RESULT, str, YES);
  }

  if (is_func_ret_charp_no_args(elem)) {
    ret_charp_no_args_func f = get_binary_function(cmd);
    char *res = f();
    print_info_msg(RESULT, res, YES);
  }

  if (is_func_ret_bool_no_args(elem)) {
    ret_bool_no_args_func f = get_binary_function(cmd);

    char str[COMMON_TEXT_SIZE] = {0};
    strcpy(str, (f() ? "TRUE" : "FALSE"));

    print_info_msg(RESULT, str, YES);
  }
}

bool is_func_no_ret_no_args(const plugin_element *elem) {
  if (strcmp(elem->descriptor.ret_val, IS_RET_VOID) == 0) {
    if (strcmp(elem->descriptor.args, NO_ARGS) == 0) {
      return true;
    }
  }

  return false;
}

bool is_func_ret_int_no_args(const plugin_element *elem) {
  if (strcmp(elem->descriptor.ret_val, IS_RET_INT) == 0) {
    if (strcmp(elem->descriptor.args, NO_ARGS) == 0) {
      return true;
    }
  }
  return false;
}

bool is_func_ret_charp_no_args(const plugin_element *elem) {
  if (strcmp(elem->descriptor.ret_val, IS_RET_CHAR_P) == 0) {
    if (strcmp(elem->descriptor.args, NO_ARGS) == 0) {
      return true;
    }
  }
  return false;
}

bool is_func_ret_bool_no_args(const plugin_element *elem) {
  if (strcmp(elem->descriptor.ret_val, IS_RET_BOOL) == 0) {
    if (strcmp(elem->descriptor.args, NO_ARGS) == 0) {
      return true;
    }
  }
  return false;
}
