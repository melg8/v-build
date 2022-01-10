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

typedef void *(*void_func)();

static char *charp_args[ARGS_COUNT] = {NULL};
static int int_args[ARGS_COUNT] = {0};
static int bool_args[ARGS_COUNT] = {0};

static const plugin_element *_elem = NULL;

static int res_int = 0;
static bool res_bool = false;
static char *res_charp = NULL;

void_func vvf = NULL;

#define ASSIGN_FUNC_INTERNAL(f)                                                \
  f = get_binary_function(_elem->descriptor.command)

// matrix
//              0   1   2

// char(0)      0   0   0
// int(1)       0   0   0
// bool(2)      0   0   0

static int _arg_matrix[ARGS_COUNT][ARGS_COUNT] = {0};

#define M_CHAR 0
#define M_INT 1
#define M_BOOL 2

#define M_SET(type, pos) _arg_matrix[type][pos] = 1

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
      M_SET(M_CHAR, i);
    }

    if (is_arg_int(i)) {
      int_args[i] = atoi(user_input_args[i]);
      M_SET(M_INT, i);
    }

    if (is_arg_bool(i)) {
      bool_args[i] = is_entered_arg_is_bool(user_input_args[i]);
      M_SET(M_BOOL, i);
    }
  }
}

static void _run_no_args() {

  if (is_func_ret_bool(_elem)) {
    res_bool = *((bool *)vvf());
  }
  if (is_func_ret_charp(_elem)) {
    res_charp = (char *)vvf();
  }
  if (is_func_ret_int(_elem)) {
    res_int = *((int *)vvf());
  }
  if (is_func_ret_void(_elem)) {
    vvf();
  }
}

void _run_with_args() {
  for (size_t i = 0; i < _cmd_arg_counter; ++i) {
    for (size_t j = 0; j < ARGS_COUNT; ++j) {
      printf("%d ", _arg_matrix[i][j]);
    }
    printf("\n");
  }
}

void exec_bin(const plugin_element *elem) {
  _elem = elem;

  _collect_args();

  ASSIGN_FUNC_INTERNAL(vvf);

  if (!is_func_has_args(_elem)) {
    _run_no_args();
  } else {
    _run_with_args();
  }

  _print_result();
}
