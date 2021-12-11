#include "text_creation.h"

#include <string.h>

#include "os_global.h"

char *generate_error_string(const char *text) {
  char string[ERROR_TEXT_LEN];
  strcpy(string, OS_COLOR_RED);
  strcat(string, "Error: ");
  strcat(string, text);
  strcat(string, OS_NO_COLOR);
  strcat(string, "\n\0");
  return strdup(string);
}
