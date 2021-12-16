#include "plugin_parser.h"

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "text_processing.h"

static u_int pos = 0;

int _read_plugin(const char *restrict plugin_path);

bool _is_eq(const char *line, const char *cmp);

void _parse_line(const char *line, int values, ...);

int load_plugin(const char *plugin_path) {
  int ret = 0;
  if (plugin_path == NULL)
    ret = -1;
  else {
    ret = _read_plugin(plugin_path);
  }
  return ret;
}

int _read_plugin(const char *restrict plugin_path) {
  FILE *pf = fopen(plugin_path, "r");
  char *line = malloc(COMMON_TEXT_SIZE);
  char temp[COMMON_TEXT_SIZE];
  size_t n;
  ssize_t read;
  plugin pl = {0};

  if (pf == NULL) {
    char err[COMMON_TEXT_SIZE] = " _read_plugin, ";
    strcat(err, strerror(errno));
    print_info_msg(ERROR_MSG, err, YES);
    return -1;
  }

  while ((read = getline(&line, &n, pf)) != -1) {
    if (line[0] == '#' || line[0] == '\n')
      continue;

    if (_is_eq(line, P_BEGIN)) {
      // start parsing;
      _parse_line(line, 6, P_NAME, P_TYPE, P_ALIAS, P_DIR, P_EXEC, P_DESC);
    }

    if (_is_eq(line, P_END)) {
      // pos++;
      // continue;
    }

    continue;

    if (strncmp(line, P_NAME, strlen(P_NAME)) == 0) {
      strcpy(temp, line + (strlen(P_NAME)));
      temp[strcspn(temp, "\n")] = 0;
      strcpy(pl.plugin_name, temp);
    }

    if (strncmp(line, P_TYPE, strlen(P_TYPE)) == 0) {
      strcpy(temp, line + (strlen(P_TYPE)));
      temp[strcspn(temp, "\n")] = 0;
      strcpy(pl.type, temp);
    }

    if (strncmp(line, P_ALIAS, strlen(P_ALIAS)) == 0) {
      strcpy(temp, line + (strlen(P_ALIAS)));
      temp[strcspn(temp, "\n")] = 0;
      strcpy(pl.alias, temp);
    }

    if (strncmp(line, P_DIR, strlen(P_DIR)) == 0) {
      strcpy(temp, line + (strlen(P_DIR)));
      temp[strcspn(temp, "\n")] = 0;
      strcpy(pl.dir, temp);
    }

    if (strncmp(line, P_EXEC, strlen(P_EXEC)) == 0) {
      strcpy(temp, line + (strlen(P_EXEC)));
      temp[strcspn(temp, "\n")] = 0;
      strcpy(pl.exec, temp);
    }

    if (strncmp(line, P_DESC, strlen(P_DESC)) == 0) {
      strcpy(temp, line + (strlen(P_DESC)));
      temp[strcspn(temp, "\n")] = 0;
      strcpy(pl.desc, temp);
      pos++;
    }

    if (strncmp(line, P_END, strlen(P_END)) == 0) {
      pos++;
    }
  }

  free(line);
  return 0;
}

bool _is_eq(const char *line, const char *cmp) {
  return strncmp(line, cmp, strlen(cmp)) == 0;
}

void _parse_line(const char *line, int values, ...) {
  va_list arg_list;
  va_start(arg_list, values);

  for (int i = 0; i < values; ++i) {
    char *str = va_arg(arg_list, char *);
    printf("arg: %s\n", str);
  }
}
