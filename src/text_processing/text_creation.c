#include "text_creation.h"

#include <stdio.h>
#include <string.h>

#include "os_global.h"

size_t get_biggest_help_length();

char *generate_help_string() {
  size_t help_string_count = sizeof(help_cmds) / sizeof(help_cmds[0]);
  size_t biggest_space = get_biggest_help_length(), current_length = 0;
  char string[HELP_STRING_LENGTH];

  memset(string, 0, HELP_STRING_LENGTH);

  for (size_t i = 0; i < help_string_count; ++i) {
    if (i == 0) {
      strcpy(string, OS_COLOR_YELLOW);
    }
    strcat(string, "\t[ ");
    strcat(string, help_cmds[i].full_name);
    strcat(string, ", ");
    strcat(string, help_cmds[i].short_name);
    strcat(string, " ]");

    current_length =
        strlen(help_cmds[i].full_name) + strlen(help_cmds[i].short_name);

    for (size_t j = 0; j < biggest_space - current_length; ++j) {
      strcat(string, " ");
    }

    strcat(string, "   -   ");
    strcat(string, help_cmds[i].desc);
    strcat(string, "\n");

    current_length = 0;
  }
  strcat(string, OS_NO_COLOR);
  strcat(string, "\0");

  return strdup(string);
}

size_t get_biggest_help_length() {
  size_t help_string_count = sizeof(help_cmds) / sizeof(help_cmds[0]);

  size_t string_size = 0;

  for (size_t i = 0; i < help_string_count; ++i) {
    size_t string_size_temp =
        sizeof(help_cmds[i].full_name) + sizeof(help_cmds[i].short_name);

    if (string_size_temp > string_size) {
      string_size = string_size_temp;
    }
  }

  return string_size;
}
