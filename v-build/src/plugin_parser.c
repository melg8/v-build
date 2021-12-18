#include "plugin_parser.h"

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static u_int _pos = 0;
static bool _ready_to_load = false;

int _load_plugin(const char *restrict plugin_path);
bool _is_eq(const char *line, const char *cmp);
void _parse_line(const char *line, plugin_descriptor *pd, int count, ...);
void _erase_list();
size_t _get_offset(int value);

plugin_element list[PLUGIN_LIST_SIZE] = {0};

int _load_plugin(const char *restrict plugin_name) {
  FILE *pf = fopen(plugin_name, "r");
  char *line = malloc(COMMON_TEXT_SIZE);
  size_t n;
  ssize_t read;
  plugin_descriptor p_desc = {0};

  if (pf == NULL) {
    char err[COMMON_TEXT_SIZE] = " _load_plugin, ";
    strcat(err, strerror(errno));
    printf("error: %s\n", err);
    return -1;
  }

  while ((read = getline(&line, &n, pf)) != -1) {
    if (line[0] == '#' || line[0] == '\n')
      continue;

    if (_is_eq(line, P_BEGIN)) {
      _ready_to_load = true;
      continue;
    }

    if (_ready_to_load) {
      _parse_line(line, &p_desc, 6, P_TYPE, P_NAME, P_EXEC, P_RET_VAL, P_ARGS,
                  P_DESC);
    }

    if (_is_eq(line, P_END)) {
      _ready_to_load = false;
      strcpy(list[_pos].plugin_name, plugin_name);
      memcpy(&list[_pos].desc, &p_desc, sizeof(p_desc));
      memset(&p_desc, 0, sizeof(p_desc));
      _pos++;
    }
  }

  free(line);
  return 0;
}

bool _is_eq(const char *line, const char *cmp) {
  return strncmp(line, cmp, strlen(cmp)) == 0;
}

void _parse_line(const char *line, plugin_descriptor *pd, int count, ...) {

  char temp[COMMON_TEXT_SIZE] = {0};

  va_list arg_list;
  va_start(arg_list, count);

  for (int i = 0; i < count; ++i) {

    char *str = va_arg(arg_list, char *);

    if (strncmp(line, str, strlen(str)) == 0) {
      strcpy(temp, line + (strlen(str)));
      temp[strcspn(temp, "\n")] = 0;

      char *base = (char *)pd;
      char *offs = base + _get_offset(i);

      strcpy(offs, temp);
    }
  }
}

size_t _get_offset(int value) {
  if (value == 0)
    return offsetof(plugin_descriptor, type);
  if (value == 1)
    return offsetof(plugin_descriptor, name);
  if (value == 2)
    return offsetof(plugin_descriptor, exec);
  if (value == 3)
    return offsetof(plugin_descriptor, ret_val);
  if (value == 4)
    return offsetof(plugin_descriptor, args);
  if (value == 5)
    return offsetof(plugin_descriptor, desc);
  return 0;
}

void _erase_list() { memset(list, 0, sizeof(list)); }
