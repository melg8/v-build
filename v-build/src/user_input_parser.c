#include "user_input_parser.h"

#include <stdio.h>
#include <string.h>

#include "io.h"

char user_args[ARGS_COUNT] = {0};

static size_t cnt = 0;

void exec_plugin_command(const char *cmd) {
  plugin_element *elem = find_element_by_command(cmd);

  if (elem == NULL) {
    print_info_msg(ERROR_MSG, "Strange behaviour, command not found", YES);
    return;
  }

  if (is_elem_binary(elem)) {
    voidfunc f = get_binary_function(cmd);
    if (strcmp(elem->descriptor.args, NO_ARGS) != 0) {
      char *str = get_input("Enter args:");
      parse_args(str);
    }
  }
}

void parse_args(const char *user_input) {
  char copy[COMMON_TEXT_SIZE];
  strcpy(copy, user_input);
  char delim = ' ';
  char *p = NULL;

  char *t1 = user_args;
  size_t *t2 = &cnt;

  memset(user_args, 0, sizeof(user_args));
  cnt = 0;

  while ((p = strtok(copy, &delim)) != NULL) {
    strcpy(&user_args[cnt], p);
    cnt++;
  }
}
