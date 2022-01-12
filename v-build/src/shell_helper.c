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
#include "plugin_parser.h"
#include "v_build_global.h"

#define PRINT_CONFIG_PARAM(param, param_readable)                              \
  ({                                                                           \
    if (param) {                                                               \
      print_info_msg(CONFIG_NAME(param_readable), GREEN_YES, YES);             \
    } else {                                                                   \
      print_info_msg(CONFIG_NAME(param_readable), RED_NO, YES);                \
    }                                                                          \
  })

void exec_help_command(const char *cmd) {

  if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0) {
    print_help();
    print_loaded_functions();
  }

  if (strcmp(cmd, "clear") == 0 || strcmp(cmd, "c") == 0) {
    CLEAR_SCREEN;
  }

  if (strcmp(cmd, "plugins") == 0 || strcmp(cmd, "p") == 0) {
    view_all_plugins();
  }

  if (strcmp(cmd, "load") == 0 || strcmp(cmd, "l") == 0) {
    // unused
  }

  if (strcmp(cmd, "set_column_args") == 0 || strcmp(cmd, "sca") == 0) {
    g_conf.is_column_args = true;
    g_conf.is_line_args = false;
    print_info_msg(COMPLETE, "column args", YES);
  }

  if (strcmp(cmd, "set_line_args") == 0 || strcmp(cmd, "sla") == 0) {
    g_conf.is_column_args = false;
    g_conf.is_line_args = true;
    print_info_msg(COMPLETE, "line args", YES);
  }

  if (strcmp(cmd, "view_config") == 0 || strcmp(cmd, "vc") == 0) {
    view_config();
  }

  if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "q") == 0) {
    EXIT(EXIT_SUCCESS);
  }
}

void print_loaded_functions() {
  char name_comparator[COMMON_TEXT_SIZE] = {0};

  for (u_int i = 0; i < get_current_list_pos(); ++i) {
    plugin_element *elem = &list[i];

    //    if (strcmp(elem->plugin_name, "plugins/io.plug") == 0)
    //      continue;

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

void print_incorrect_expected_values(size_t cur_idx, const char *expected_value,
                                     const char *entered_value) {
  char temp[COMMON_TEXT_SIZE];
  char value[10] = {0};
  strcpy(temp, "arg(");
  sprintf(value, "%lo", cur_idx);
  strcat(temp, value);
  strcat(temp, "), ");
  strcat(temp, "expected type: \"");
  strcat(temp, expected_value);
  strcat(temp, "\", ");
  strcat(temp, "entered value: \"");
  strcat(temp, entered_value);
  strcat(temp, "\"");
  print_info_msg(ERROR_MSG, temp, YES);
}

void view_config() {
  PRINT_CONFIG_PARAM(g_conf.is_column_args, "column args: ");
  PRINT_CONFIG_PARAM(g_conf.is_line_args, "line args: ");
}
