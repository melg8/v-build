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

help_func print_help_f = NULL;
char_func get_input_f = NULL;
arg_bool_func arg_bool_f = NULL;

int _check_main_plugin();
void _open_text_lib();
void *_get_binary_func_internal(const char *name);

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
  print_help_f = get_func(plugin_list, 0);
  get_input_f = get_func(plugin_list, 1);
  arg_bool_f = get_func(plugin_list, 2);
}

void construct_path(char *path, size_t pos) {
  strcpy(path, plugin_list[pos].dir);
  strcat(path, "/");
  strcat(path, plugin_list[pos].exec);
}

bool is_object_binary(const plugin *plugin_list, size_t pos) {
  return strcmp(plugin_list[pos].type, "bin") == 0;
}

void open_binary(const char *path) {
  plugin_handle = dlopen(path, RTLD_NOW | RTLD_DEEPBIND);
  if (plugin_handle == NULL) {
    printf("dlopen error: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }
}

void *_get_binary_func_internal(const char *name) {
  void *p = dlsym(plugin_handle, name);
  if (p == NULL) {
    printf("cannot open %s.\n", name);
    exit(EXIT_FAILURE);
  }
  return p;
}

void *get_func(const plugin *plugin_list, size_t pos) {
  void *f = NULL;
  char path[COMMON_TEXT_SIZE] = {0};

  construct_path(path, pos);
  open_binary(path);
  f = _get_binary_func_internal(plugin_list[pos].name);

  return f;
}
