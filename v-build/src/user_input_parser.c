#include "user_input_parser.h"

#include <stdio.h>
#include <string.h>

#include "io.h"

char user_args[ARGS_COUNT][COMMON_TEXT_SIZE] = {0};

static size_t cnt = 0;

void exec_plugin_command(const char *cmd) {
  plugin_element *elem = find_element_by_command(cmd);

  if (elem == NULL) {
    print_info_msg(ERROR_MSG, "Strange behaviour, command not found", YES);
    return;
  }

  if (is_elem_binary(elem)) {
    voidfunc f = get_binary_function(cmd);
    if (is_func_has_args(elem)) {
      char *str = elem->descriptor.args;
      parse_args(str);
      get_func_args();

      for (size_t i = 0; i < cnt; ++i) {
        print_info_msg("your arg: ", user_args[i], YES);
      }
    }
  }
}

void parse_args(const char *elem_args) {
  char copy[COMMON_TEXT_SIZE];
  strcpy(copy, elem_args);
  char delim[] = ",";
  char *p = NULL;

  memset(user_args, 0, sizeof(user_args));
  cnt = 0;

  p = strtok(copy, delim);

  // find all args
  while (p != NULL) {
    strcpy(user_args[cnt], p);
    p = strtok(NULL, delim);
    cnt++;
  }

  // remove whitespaces in args, if any exists
  for (size_t i = 0; i < cnt; ++i) {
    char temp[COMMON_TEXT_SIZE] = {0};
    strcpy(temp, user_args[i]);
    size_t spnz = strspn(temp, " ");
    strcpy(user_args[i], temp + spnz);
  }
}

bool is_func_has_args(const plugin_element *elem) {
  bool has_args = strcmp(elem->descriptor.args, NO_ARGS) != 0;
  return has_args;
}

void get_func_args() {
  char arg_type_must_be[COMMON_TEXT_SIZE] = {0};

  if (cnt == 0)
    return;

  for (size_t i = 0; i < cnt; ++i) {
    memset(arg_type_must_be, 0, sizeof(arg_type_must_be));

    strcpy(arg_type_must_be, "Enter the argument (must be ");
    strcat(arg_type_must_be, user_args[i]);
    strcat(arg_type_must_be, "): ");

    char *arg_value = get_input(arg_type_must_be);
    strcpy(user_args[i], arg_value);
  }
}
