#include "text_creation.h"

#include <stdio.h>
#include <string.h>

#include "os_global.h"

char *generate_error_string(const char *text) {
  char string[ERROR_TEXT_LEN];
  memset(string, 0, ERROR_TEXT_LEN);

  strcpy(string, OS_COLOR_RED);
  strcat(string, "Error: ");
  strcat(string, OS_NO_COLOR);
  strcat(string, text);
  strcat(string, "\n\0");
  return strdup(string);
}

char *generate_help_string() {
  size_t help_msg_count = sizeof(cmds) / sizeof(cmds[0]);

  char string[1024];
  memset(string, 0, 1024);

  for (size_t i = 0; i < help_msg_count; ++i) {
    if (i == 0) {
      strcpy(string, OS_COLOR_YELLOW);
    }
    strcat(string, cmds[i].full_name);
    strcat(string, ", ");
    strcat(string, cmds[i].short_name);
    strcat(string, "   -   ");
    strcat(string, cmds[i].desc);
    strcat(string, "\n");
  }
  strcat(string, OS_NO_COLOR);
  strcat(string, "\n\0");

  return strdup(string);
}
