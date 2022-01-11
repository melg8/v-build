#include "bin_exec.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bin_exec_internal.h"
#include "io.h"
#include "v_build_global.h"

char *charp_args[ARGS_COUNT] = {0};
int int_args[ARGS_COUNT] = {0};
int bool_args[ARGS_COUNT] = {0};

short arg_matrix[ARGS_COUNT][ARGS_COUNT] = {0};

const plugin_element *_elem = NULL;

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
  if (is_func_ret_int(_elem)) {
    char ptr[10];
    sprintf(ptr, "%d", res_int);
    print_info_msg(RETURN_VAL, ptr, YES);
  }
  if (is_func_ret_bool(_elem)) {
    void *ptr = NULL;
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
    res_bool = exec_internal_bool();
  }
  if (fcharp != NULL) {
    res_charp = exec_internal_charp();
  }
  if (fint != NULL) {
    res_int = exec_internal_int();
  }
  if (fvoid != NULL) {
    exec_internal_void();
  }
}

static void _run_with_args() {
  if (fbool != NULL) {
    res_bool = exec_internal_ret_bool_with_args();
  }
  if (fcharp != NULL) {
    res_charp = exec_internal_ret_charp_with_args();
  }
  if (fint != NULL) {
    res_int = exec_internal_ret_int_with_args();
  }
  if (fvoid != NULL) {
    exec_internal_void_args();
  }
}

static void _reset() {

  for (size_t i = 0; i < _cmd_arg_counter; ++i) {
    charp_args[i] = "NULL";
    int_args[i] = 0;
    bool_args[i] = false;
  }

  fvoid = NULL;
  fcharp = NULL;
  fint = NULL;
  fbool = NULL;
}

void exec_bin(const plugin_element *elem) {
  _elem = elem;

  _collect_args();
  _assign_func();

  if (!is_func_has_args(_elem)) {
    _run_no_args();
  } else {
    _run_with_args();
  }

  _print_result();
  _reset();
}
