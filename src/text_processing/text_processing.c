#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "os_global.h"
#include "text_creation.h"
#include "text_processing.h"

bool is_command_exist(const char *cmd) { return _is_command_exist(cmd); }

// release the string after use ( free )
char *get_command_from_user() {
  char user_command[USER_COMMAND_LEN];
  printf(OS_COLOR_GREEN SHELL_NAME OS_NO_COLOR);

  // check for the CTRL-D
  if (fgets(user_command, USER_COMMAND_LEN, stdin) == NULL) {
    printf("\n");
    EXIT(EXIT_SUCCESS);
  }

  // remove new line symbol '\n' and place 0
  user_command[strcspn(user_command, "\n")] = 0;
  return strdup(user_command);
}

void print_help_msg() {
  char *help_text = generate_help_string();
  print_msg(help_text, SLEEP_MSEC_HELP);
  free(help_text);
}

void print_error_msg(const char *msg) {
  char *text = generate_error_string(msg);
  print_msg(text, SLEEP_MSEC_COMMON);
  free(text);
}

void print_msg(const char *msg, size_t sleep_msec) {
  size_t msg_len = strlen(msg);

  for (size_t i = 0; i < msg_len; ++i) {
    putchar(msg[i]);
    fflush(stdout);
    usleep(sleep_msec);
  }
}

bool is_command_simple(const char *cmd) {
  size_t i = find_command(cmd);
  return help_cmds[i].property == SIMPLE;
}

size_t find_command(const char *cmd) {
  size_t res = -1;
  size_t cmd_count = sizeof(help_cmds) / sizeof(help_cmds[0]);

  for (size_t i = 0; i < cmd_count; ++i) {
    if (strcmp(cmd, help_cmds[i].full_name) == 0 ||
        strcmp(cmd, help_cmds[i].short_name) == 0) {
      res = i;
      break;
    }
  }
  return res;
}
