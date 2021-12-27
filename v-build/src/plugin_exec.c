#include "plugin_exec.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "binary_parser.h"
#include "io.h"
#include "stdlib.h"
#include "v_build_global.h"

// local

const plugin_element *_elem = NULL;

voidfunc vf = NULL;
intfunc intf = NULL;
boolfunc boolf = NULL;
charpfunc charpf = NULL;

bool is_ret_void() {
  return strcmp(_elem->descriptor.ret_val, IS_VALUE_VOID) == 0;
}

void run_void_func_with_args(voidfunc f) {
  if (_cmd_arg_counter == 1) {
    if (strcmp(user_args_etalon[0], IS_VALUE_INT) == 0) {
      int arg = atoi(user_input_args[0]);
      f(arg);
    }
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

void exec_plugin(const plugin_element *restrict elem) {
  _elem = elem;

  if (_elem == NULL) {
    print_info_msg(ERROR_MSG, "plugin_element is incorrect, exit");
    EXIT(EXIT_FAILURE);
  }

  if (is_ret_void()) {
    exec_void_func();
  }
}
