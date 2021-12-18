#include "io.h"

#include <stdio.h>

// function from io_lib, loading by default
void (*greetings)();
void (*print_help)();
void (*print_msg)(const char *msg, size_t sleep_msec);
void (*print_info_msg)(const char *title, const char *msg, int newline_symbol);
int (*ask_yes_no)(const char *question_text);

void _get_io_funcs();

int load_io() {
  if (load_plugin(IO_PLUGIN_NAME) == -1) {
    printf("%s: plugin loading error, exit.\n", IO_PLUGIN_NAME);
    return -1;
  } else {
    _get_io_funcs();
  }

  return 0;
}

void _get_io_funcs() {
  greetings = get_binary_function("greetings");
  print_help = get_binary_function("print_help_msg");
  print_msg = get_binary_function("print_msg");
  print_info_msg = get_binary_function("print_info_msg");
  ask_yes_no = get_binary_function("ask_yes_no");
}
