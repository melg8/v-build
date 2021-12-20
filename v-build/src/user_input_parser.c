#include "user_input_parser.h"

#include <string.h>

void exec_plugin_command(const char *cmd) {
  plugin_element *elem = find_element_by_command(cmd);

  if (elem == NULL)
    return;

  if (is_func_void_no_ret(elem)) {
    ret_void_no_args_func f = get_binary_function(cmd);
    f();
  }
}

bool is_func_void_no_ret(const plugin_element *elem) {
  if (is_elem_binary(elem)) {
    if (strcmp(elem->descriptor.ret_val, IS_RET_VOID) == 0) {
      if (strcmp(elem->descriptor.args, NO_ARGS) == 0) {
        return true;
      }
    }
  }
  return false;
}
