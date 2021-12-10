#include <stdio.h>
#include <stdlib.h>

#include "os_global.h"
#include "text_processor.h"

void process_string() {}

// release the string after use
char *get_command_from_user() {
  char *user_string = malloc(64);
  printf(OS_COLOR_GREEN SHELL_NAME OS_NO_COLOR);
  scanf("%s", user_string);

  return user_string;
}
