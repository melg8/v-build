#include "autoload.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "plugin.h"
#include "v_build_global.h"

static bool _is_eq(const char *line, const char *cmp);
static bool _ready_to_load = false;

void autoload_plugins() {
  FILE *pf = fopen(AUTOLOAD_FILE, "r");
  char *line = malloc(COMMON_TEXT_SIZE);
  size_t n;
  ssize_t read;

  if (pf == NULL) {
    char err[COMMON_TEXT_SIZE] = " file autoload.config, ";
    strcat(err, strerror(errno));
    printf("error: %s\n", err);
    return;
  }

  while ((read = getline(&line, &n, pf)) != -1) {
    if (line[0] == '#' || line[0] == '\n')
      continue;

    if (_is_eq(line, P_BEGIN)) {
      _ready_to_load = true;
      continue;
    }

    if (_ready_to_load) {
      // char
      if (_is_eq(line, P_END)) {
        _ready_to_load = false;
        continue;
      }
      char plugin_path[COMMON_TEXT_SIZE];
      strcpy(plugin_path, line);
      plugin_path[strcspn(plugin_path, "\n")] = 0;

      if (load_plugin(plugin_path) == -1) {
        printf("%s: plugin loading error, exit.\n", plugin_path);
        exit(EXIT_FAILURE);
      }
    }
  }

  fclose(pf);
  free(line);
}

static bool _is_eq(const char *line, const char *cmp) {
  return strncmp(line, cmp, strlen(cmp)) == 0;
}
