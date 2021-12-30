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

static char *charp_args[ARGS_COUNT] = {0};
static int int_args[ARGS_COUNT] = {0};
static bool bool_args[ARGS_COUNT] = {0};

static const plugin_element *_elem = NULL;

static int res_int = 0;
static bool res_bool = false;
static char *res_charp = NULL;

void_f fv = NULL;
int_f fi = NULL;
char_f fc = NULL;
bool_f fb = NULL;

#define ASSIGN_FUNC(f) f = get_binary_function(_elem->descriptor.command)

void print_result() {
  char *p = NULL;
  if (is_func_ret_int(_elem)) {
    p = malloc(sizeof(int));
    sprintf(p, "%d", res_int);
    print_info_msg(RETURN_VAL, p, YES);
    free(p);
  }
  if (is_func_ret_bool(_elem)) {
    p = malloc(COMMON_TEXT_SIZE);
    if (res_bool == false) {
      strcpy(p, "false");
    } else if (res_bool == true) {
      strcpy(p, "true");
    }
    print_info_msg(RETURN_VAL, p, YES);
    free(p);
  }
  if (is_func_ret_charp(_elem)) {
    print_info_msg(RETURN_VAL, res_charp, YES);
  }
}

void exec_bin(const plugin_element *elem) {
  _elem = elem;

  for (size_t i = 0; i < _cmd_arg_counter; ++i) {
    if (is_arg_charp(i)) {
      charp_args[i] = user_input_args[i];
    }

    if (is_arg_int(i)) {
      int_args[i] = atoi(user_input_args[i]);
    }

    if (is_arg_bool(i)) {
      bool_args[i] = user_input_args[i];
    }
  }
}
