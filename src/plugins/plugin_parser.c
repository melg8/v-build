#include "plugin_parser.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "text_processing.h"

static u_int list_pos = 0;

void _read_plugin(const char *restrict plugin_path);
void _parse_line(const char *restrict line);

int load_plugin(const char *plugin_path) {
  if (plugin_path == NULL)
    return -1;
  else {
    _read_plugin(plugin_path);
  }
  return 0;
}

void _read_plugin(const char *restrict plugin_path) {
  FILE *pf = fopen(plugin_path, "r");
  char *line = malloc(COMMON_TEXT_SIZE);
  size_t n;
  ssize_t read;

  if (pf == NULL) {
    char err[COMMON_TEXT_SIZE] = " _read_plugin, ";
    strcat(err, strerror(errno));
    print_info_msg(ERROR_MSG, err, YES);
  }

  while ((read = getline(&line, &n, pf)) != -1) {
    // parse_line
    _parse_line(line);
  }

  free(line);
}

void _parse_line(const char *line) {
  if (line[0] == '#' || line[0] == '\n') {
    return;
  } else {
    print_info_msg(COMPLETE, line, NO);
  }
}
