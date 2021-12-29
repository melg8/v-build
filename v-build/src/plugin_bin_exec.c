#include "plugin_bin_exec.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "binary_parser.h"
#include "io.h"
#include "stdlib.h"
#include "v_build_global.h"

// local

#define T_INT(idx) atoi(user_input_args[idx])
#define T_CHARP(idx) user_input_args[idx]
#define T_BOOL(idx)                                                            \
  (strcmp(user_input_args[idx], "1") == 0) ||                                  \
      (strcmp(user_input_args[idx], "TRUE") == 0) ||                           \
      (strcmp(user_input_args[idx], "true") == 0)

union Data {
  int integer;
  bool boolean;
  char *charp;
};

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

  union Data data[_cmd_arg_counter];

  for (size_t i = 0; i < _cmd_arg_counter; ++i) {

    if (is_arg_int(i)) {
      data[i].integer = T_INT(i);
    }

    if (is_arg_charp(i)) {
      data[i].charp = T_CHARP(i);
    }

    if (is_arg_bool(i)) {
      data[i].boolean = T_BOOL(i);
    }
  }

  switch (_cmd_arg_counter) {
  case 1:
    f(data[0]);
    break;
  case 2:
    f(data[0], data[1]);
    break;
  case 3:
    f(data[0], data[1], data[2]);
    break;
  default:
    break;
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
