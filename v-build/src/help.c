#include "help.h"

#include <stdbool.h>
#include <string.h>

#include "io.h"
#include "plugin.h"
#include "v_build_global.h"

typedef struct counter {
  char plugin_name[COMMON_TEXT_SIZE];
  u_int func_count;
} counter;

void print_loaded_functions() {
  char name_comparator[COMMON_TEXT_SIZE] = {0};

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
    }

    print_info_msg("\t", elem->descriptor.command, YES);
  }
  print_msg("\n");
}
