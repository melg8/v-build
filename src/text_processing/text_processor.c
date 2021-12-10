#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os_global.h"
#include "text_processor.h"

void process_string() {}

// release the string after use
char *get_command_from_user() {
  char user_command[USER_COMMAND_LEN];
  printf(OS_COLOR_GREEN SHELL_NAME OS_NO_COLOR);
  scanf("%s", user_command);
  return strdup(user_command);
}
