#include "plugin_parser.h"

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "text_processing.h"

static plugin plugin_list[PLUGIN_LIST_SIZE];
static u_int pos = 0;

void _read_plugin(const char *restrict plugin_path);

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
  char temp[COMMON_TEXT_SIZE];
  size_t n;
  ssize_t read;
  plugin pl;

  if (pf == NULL) {
    char err[COMMON_TEXT_SIZE] = " _read_plugin, ";
    strcat(err, strerror(errno));
    print_info_msg(ERROR_MSG, err, YES);
  }

  while ((read = getline(&line, &n, pf)) != -1) {
    if (line[0] == '#' || line[0] == '\n')
      continue;

    memset(temp, 0, COMMON_TEXT_SIZE);

    if (strncmp(line, P_NAME, strlen(P_NAME)) == 0) {
      strcpy(temp, line + (strlen(P_NAME)));
      temp[strcspn(temp, "\n")] = 0;
      strcpy(pl.plugin_name, temp);
      strcpy(plugin_list[pos].plugin_name, temp);
      break;
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
}
