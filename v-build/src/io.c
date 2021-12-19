#include "io.h"

#include <stdio.h>

// function from io_lib, loading by default
void (*greetings)();
void (*print_help)();
void (*print_msg)(const char *msg, size_t sleep_msec);
void (*print_info_msg)(const char *title, const char *msg, int newline_symbol);
int (*ask_yes_no)(const char *question_text);
bool (*is_command_exist)(const char *cmd);
char *(*get_shell_input)();
char *(*get_input)();
// end io lib

void load_io() {
  greetings = get_binary_function("greetings");
  print_help = get_binary_function("print_help_msg");
  print_msg = get_binary_function("print_msg");
  print_info_msg = get_binary_function("print_info_msg");
  ask_yes_no = get_binary_function("ask_yes_no");
}
