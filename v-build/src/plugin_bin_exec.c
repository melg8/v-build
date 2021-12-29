#include "plugin_bin_exec.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include "io.h"
#include "stdlib.h"
#include "v_build_global.h"

// local

static const plugin_element *_elem = NULL;

void_p_func vf = NULL;

static bool is_ret_void() {
  return strcmp(_elem->descriptor.ret_val, IS_VALUE_VOID) == 0;
}

static bool is_arg_int(size_t idx) {
  return strcmp(user_args_etalon[idx], IS_VALUE_INT) == 0;
}

static bool is_arg_charp(size_t idx) {
  return strcmp(user_args_etalon[idx], IS_VALUE_CHAR_P) == 0;
}

static bool is_arg_bool(size_t idx) {
  return strcmp(user_args_etalon[idx], IS_VALUE_BOOL) == 0;
}

void run_void_func_with_args(void_p_func f) {

  if (is_arg_int(0) && is_arg_int(1) && is_arg_int(2)) {
    int value_1 = atoi(user_input_args[0]);
    int value_2 = atoi(user_input_args[1]);
    int value_3 = atoi(user_input_args[2]);

    f(value_1, value_2, value_3);
  }

  if (is_arg_int(0) && is_arg_int(0) && is_arg_bool(1)) {
    f(*(int *)(user_input_args[0]), *(int *)(user_input_args[1]),
      *(bool *)(user_input_args[2]));
  }

  if (is_arg_charp(0) && is_arg_charp(1) && is_arg_bool(2)) {
    f(T_CHARP(0), T_CHARP(1), T_BOOL(2));
  }
}

void exec_void_func() {
  vf = get_binary_function(_elem->descriptor.command);

  if (!is_func_has_args(_elem)) {
    vf();
  } else {
    run_void_func_with_args(vf);
  }
}

// global

void exec_bin(const plugin_element *elem) {
  _elem = elem;

  if (_elem == NULL) {
    print_info_msg(ERROR_MSG, "plugin_element is incorrect, exit");
    EXIT(EXIT_FAILURE);
  }

  if (is_ret_void()) {
    exec_void_func();
  }
}
