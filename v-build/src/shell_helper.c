#include "shell_helper.h"

#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "io.h"
#include "plugin.h"
#include "v_build_global.h"

typedef struct counter {
  char plugin_name[COMMON_TEXT_SIZE];
  u_int func_count;
} counter;

void exec_help_command(const char *cmd) {

  if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0) {
    print_help();
    print_loaded_functions();
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

void print_loaded_functions() {
  char name_comparator[COMMON_TEXT_SIZE] = {0};

  print_msg("\n", 0);
  print_info_msg("Loaded plugins:", "", YES);

  for (u_int i = 0; i < get_current_list_pos(); ++i) {
    plugin_element *elem = &list[i];
    if (strcmp(name_comparator, elem->plugin_name) != 0) {
      char temp[COMMON_TEXT_SIZE] = {0};
      strcpy(temp, "\n");
      strcat(temp, OS_COLOR_BLUE);
      strcpy(name_comparator, elem->plugin_name);
      strcat(temp, name_comparator);
      strcat(temp, OS_NO_COLOR);
      print_info_msg(temp, ":", YES);

      memset(temp, 0, sizeof(temp));

      strcpy(temp, OS_COLOR_YELLOW);
      print_fmt_msg(0, temp);

      memset(temp, 0, sizeof(temp));
      strcat(temp, "type:");
      print_fmt_msg(8, temp);

      strcpy(temp, "command:");
      print_fmt_msg(30, temp);

      strcpy(temp, "return");
      print_fmt_msg(10, temp);

      strcpy(temp, "args:");
      print_fmt_msg(35, temp);

      strcpy(temp, "description:");
      print_fmt_msg(50, temp);

      strcpy(temp, OS_NO_COLOR);
      strcat(temp, "\n");
      print_msg(temp, 0);
    }

    print_fmt_msg(8, elem->descriptor.type);
    print_fmt_msg(30, elem->descriptor.command);
    print_fmt_msg(10, elem->descriptor.ret_val);
    print_fmt_msg(35, elem->descriptor.args);
    print_fmt_msg(50, elem->descriptor.desc);

    print_msg("\n", 0);
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
  strcat(plugins, OS_NO_COLOR);
  print_info_msg(OS_COLOR_YELLOW, plugins, YES);
}
