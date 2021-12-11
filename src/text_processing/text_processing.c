#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "os_global.h"
#include "text_creation.h"
#include "text_processing.h"

bool is_command_exist(const char *cmd) { return _is_command_exist(cmd); }

// release the string after use
char *get_command_from_user() {
  char user_command[USER_COMMAND_LEN];
  printf(OS_COLOR_GREEN SHELL_NAME OS_NO_COLOR);
  scanf("%s", user_command);
  return strdup(user_command);
}

void print_help_msg() {
  char *help_text = generate_help_string();
  write_msg(help_text, SLEEP_MSEC_HELP);
  free(help_text);
}

void error_msg(const char *msg) {
  char *text = generate_error_string(msg);
  write_msg(text, SLEEP_MSEC_COMMON);
  free(text);
}

void write_msg(const char *msg, size_t sleep_msec) {
  size_t msg_len = strlen(msg);

  for (size_t i = 0; i < msg_len; ++i) {
    putchar(msg[i]);
    fflush(stdout);
    usleep(sleep_msec);
  }
}
