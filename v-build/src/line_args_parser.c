#include "line_args_parser.h"

#include <ctype.h>

#include "io.h"
#include "string.h"
#include "v_build_global.h"

static size_t _len = 0;
static char _command[COMMON_TEXT_SIZE] = {0};

char *get_command_from_line(const char *cmd_line) {
  char delim = ' ';
  _len = strcspn(cmd_line, &delim);
  // return strndup(cmd_line, _len);

  strncpy(_command, cmd_line, _len);

  return _command;
}

void fill_line_args() {}
