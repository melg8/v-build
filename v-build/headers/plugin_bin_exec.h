#ifndef PLUGIN_BIN_EXEC_H
#define PLUGIN_BIN_EXEC_H

#include <string.h>

#include "binary_parser.h"
#include "plugin.h"

#define T_INT(idx) atoi(user_input_args[idx])
#define T_CHARP(idx) user_input_args[idx]
#define T_BOOL(idx)                                                            \
  (strcmp(user_input_args[idx], "1") == 0) ||                                  \
      (strcmp(user_input_args[idx], "TRUE") == 0) ||                           \
      (strcmp(user_input_args[idx], "true") == 0)

void exec_bin(const plugin_element *elem);

#endif // PLUGIN_BIN_EXEC_H
