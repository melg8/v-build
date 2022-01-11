#ifndef BIN_EXEC_INTERNAL_H
#define BIN_EXEC_INTERNAL_H

#include <stdbool.h>

#include "bin_exec.h"
#include "plugin.h"
#include "plugin_parser.h"

void exec_internal_void();
bool exec_internal_bool();
int exec_internal_int();
char *exec_internal_charp();

void exec_internal_void_args();
bool exec_internal_ret_bool_with_args();
int exec_internal_ret_int_with_args();
char *exec_internal_ret_charp_with_args();

#endif // BIN_EXEC_INTERNAL_H
