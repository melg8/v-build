#include "shell.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "io.h"
#include "v_build_global.h"

void run_shell() {
  load_io();

  RUN_SHELL_LOOP {
    char *user_input = get_shell_input();

    if (is_help_command_exist(user_input)) {
      exec_help_command(user_input);
    } else {
      print_info_msg(ERROR_MSG, INVALID_COMMAND, YES);
    }
  }
}

void exec_help_command(const char *cmd) {

  if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0) {
    print_help();
  }

  if (strcmp(cmd, "clear") == 0 || strcmp(cmd, "c") == 0) {
    CLEAR_SCREEN;
  }

  if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "q") == 0) {
    EXIT(EXIT_SUCCESS);
  }

  if (strcmp(cmd, "plugins") == 0 || strcmp(cmd, "p") == 0) {
    view_all_plugins();
  }

  if (strcmp(cmd, "load") == 0 || strcmp(cmd, "l") == 0) {
    // load plugin
  }
}

void view_all_plugins() {
  DIR *d = opendir("plugins");
  struct dirent *dp = NULL;
  char plugins[COMMON_TEXT_SIZE * 2] = {0};
  strcpy(plugins, "\n");

  if (d == NULL) {
    print_info_msg(ERROR_MSG, strerror(errno), YES);
    return;
  }

  while ((dp = readdir(d)) != 0) {

    if (strstr(dp->d_name, ".plug") != NULL) {
      strcat(plugins, dp->d_name);
      strcat(plugins, "\n");
    }
  }
  print_info_msg(COMPLETE, plugins, YES);
}
