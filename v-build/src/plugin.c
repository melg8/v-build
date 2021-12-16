#include "plugin.h"

#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "plugin_parser.h"

typedef void (*print_help_func)();

static char *cur_pwd = NULL;
static char full_plugin_path[COMMON_TEXT_SIZE];

int _check_main_plugin();

void _open_text_lib();

bool is_text_plugin_loaded() {
  if (_check_main_plugin() != 0) {
    printf("common plugin not loaded\n");
    return false;
  }
  if (load_plugin(full_plugin_path) != 0) {
    printf("common plugin not loaded\n");
    return false;
  }

  for (int i = 0; i < 3; ++i) {
    printf("%d) type: %s\n", i, plugin_list[i].type);
    printf("%d) name: %s\n", i, plugin_list[i].name);
    printf("%d) dir: %s\n", i, plugin_list[i].dir);
    printf("%d) exec: %s\n", i, plugin_list[i].exec);
    printf("%d) args: %s\n", i, plugin_list[i].args);
    printf("%d) desc: %s\n", i, plugin_list[i].desc);
  }

  _open_text_lib();

  return true;
}

int _check_main_plugin() {
  cur_pwd = getenv("PWD");
  struct stat st;

  if (cur_pwd == NULL) {
    printf("cannot find PWD environment variable.\n");
    exit(EXIT_FAILURE);
  }

  strcpy(full_plugin_path, cur_pwd);
  strcat(full_plugin_path, "/");
  strcat(full_plugin_path, MAIN_PLUGIN);

  if (stat(full_plugin_path, &st) == -1) {
    char err[COMMON_TEXT_SIZE];
    strcpy(err, full_plugin_path);
    strcat(err, ", ");
    strcat(err, strerror(errno));
    return -1;
  }

  // if file is not regular
  if (!S_ISREG(st.st_mode)) {
    return -1;
  }
  return 0;
}

void _open_text_lib() {
  plugin *text_plugin = &plugin_list[0];
  print_help_func phf = NULL;
  void *text_handle = NULL;
  char path[COMMON_TEXT_SIZE] = {0};
  strcpy(path, text_plugin->dir);
  strcat(path, "/");
  strcat(path, text_plugin->exec);

  if (strcmp(text_plugin->name, "print_help_msg") == 0) {

    text_handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);

    if (text_handle == NULL) {
      printf("dlopen error: %s\n", dlerror());
      exit(EXIT_FAILURE);
    }

    phf = dlsym(text_handle, text_plugin->name);
    if (phf == NULL) {
      printf("cannot open text lib.\n");
      exit(EXIT_FAILURE);
    }

    phf();

  } else {
    printf("main.plug is incorrect, exit\n");
    exit(EXIT_FAILURE);
  }
}
