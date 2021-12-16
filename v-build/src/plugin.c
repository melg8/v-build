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

static char *cur_pwd = NULL;
static char full_plugin_path[COMMON_TEXT_SIZE];
void *plugin_handle = NULL;

void_func vf = NULL;
char_func chf = NULL;

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

  for (int i = 0; i < 5; ++i) {
    printf("%d) type: %s\n", i, plugin_list[i].type);
    printf("%d) name: %s\n", i, plugin_list[i].name);
    printf("%d) dir: %s\n", i, plugin_list[i].dir);
    printf("%d) exec: %s\n", i, plugin_list[i].exec);
    printf("%d) ret_val: %s\n", i, plugin_list[i].ret_val);
    printf("%d) args: %s\n", i, plugin_list[i].args);
    printf("%d) desc: %s\n\n", i, plugin_list[i].desc);
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
  vf = get_void_func(plugin_list, 0);
  chf = get_char_func(plugin_list, 1);
}

void_func get_void_func(const plugin *plugin_list, size_t pos) {
  void_func vf = NULL;
  char path[COMMON_TEXT_SIZE] = {0};
  strcpy(path, plugin_list[0].dir);
  strcat(path, "/");
  strcat(path, plugin_list[pos].exec);

  plugin_handle = dlopen(path, RTLD_NOW | RTLD_DEEPBIND);
  if (plugin_handle == NULL) {
    printf("dlopen error: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  vf = dlsym(plugin_handle, plugin_list[0].name);
  if (vf == NULL) {
    printf("cannot open %s.\n", plugin_list[0].name);
    exit(EXIT_FAILURE);
  }

  return vf;
}

void print_help() { vf(); }

char_func get_char_func(const plugin *plugin_list, size_t pos) {
  char_func chf = NULL;
  char path[COMMON_TEXT_SIZE] = {0};
  strcpy(path, plugin_list[pos].dir);
  strcat(path, "/");
  strcat(path, plugin_list[pos].exec);

  plugin_handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
  if (plugin_handle == NULL) {
    printf("dlopen error: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  chf = dlsym(plugin_handle, plugin_list[pos].name);
  if (chf == NULL) {
    printf("cannot open %s.\n", plugin_list[pos].name);
    exit(EXIT_FAILURE);
  }

  return chf;
}

void get_input_from_user() { char *ch = chf(); }
