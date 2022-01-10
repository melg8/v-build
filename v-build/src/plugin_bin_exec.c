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

static char *charp_args[ARGS_COUNT] = {NULL};
static int int_args[ARGS_COUNT] = {0};
static int bool_args[ARGS_COUNT] = {0};

static const plugin_element *_elem = NULL;

static int res_int = 0;
static bool res_bool = false;
static char *res_charp = NULL;

void_f fvoid = NULL;
int_f fint = NULL;
char_f fcharp = NULL;
bool_f fbool = NULL;

#define ASSIGN_FUNC_INTERNAL(f)                                                \
  f = get_binary_function(_elem->descriptor.command)

static void _print_result() {
  void *ptr = NULL;
  if (is_func_ret_int(_elem)) {
    ptr = malloc(sizeof(int));
    sprintf(ptr, "%d", res_int);
    print_info_msg(RETURN_VAL, ptr, YES);
    free(ptr);
  }
  if (is_func_ret_bool(_elem)) {
    ptr = malloc(COMMON_TEXT_SIZE);
    if (res_bool == false) {
      strcpy(ptr, "false");
    } else if (res_bool == true) {
      strcpy(ptr, "true");
    }
    print_info_msg(RETURN_VAL, ptr, YES);
    free(ptr);
  }
  if (is_func_ret_charp(_elem)) {
    print_info_msg(RETURN_VAL, res_charp, YES);
  }
}

static void _collect_args() {
  for (size_t i = 0; i < _cmd_arg_counter; ++i) {
    if (is_arg_charp(i)) {
      charp_args[i] = user_input_args[i];
    }

    if (is_arg_int(i)) {
      int_args[i] = atoi(user_input_args[i]);
    }

    if (is_arg_bool(i)) {
      bool_args[i] = is_entered_arg_is_bool(user_input_args[i]);
    }
  }
}

static void _assign_func() {
  if (is_func_ret_bool(_elem)) {
    ASSIGN_FUNC_INTERNAL(fbool);
  }
  if (is_func_ret_charp(_elem)) {
    ASSIGN_FUNC_INTERNAL(fcharp);
  }
  if (is_func_ret_int(_elem)) {
    ASSIGN_FUNC_INTERNAL(fint);
  }
  if (is_func_ret_void(_elem)) {
    ASSIGN_FUNC_INTERNAL(fvoid);
  }
}

static void _run_no_args() {
  if (fbool != NULL) {
    res_bool = fbool();
  }
  if (fcharp != NULL) {
    res_charp = fcharp();
  }
  if (fint != NULL) {
    res_int = fint();
  }
  if (fvoid != NULL) {
    fvoid();
  }
}

void exec_bin(const plugin_element *elem) {
  _elem = elem;

  _collect_args();
  _assign_func();

  if (!is_func_has_args(_elem)) {
    _run_no_args();
  }

  _print_result();
}
