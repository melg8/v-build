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

typedef void (*void_f)();
typedef int (*int_f)();
typedef char *(*char_f)();
typedef bool (*bool_f)();

static char *ch_args[ARGS_COUNT] = {0};
static int int_args[ARGS_COUNT] = {0};
static bool bool_args[ARGS_COUNT] = {0};

static const plugin_element *_elem = NULL;

void run_matrix() {
  switch (_cmd_arg_counter) {
  case 0:
    break;
  default:
    break;
  }
}

void exec_bin(const plugin_element *elem) {
  _elem = elem;

  for (size_t i = 0; i < _cmd_arg_counter; ++i) {
    if (is_arg_char(i)) {
      ch_args[i] = user_input_args[i];
    }

    if (is_arg_int(i)) {
      int_args[i] = atoi(user_input_args[i]);
    }

    if (is_arg_bool(i)) {
      bool_args[i] = user_input_args[i];
    }
  }

  run_matrix();
}
