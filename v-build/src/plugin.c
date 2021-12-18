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

void *plugin_handle = NULL;

int load_plugin(const char *plugin_name) {
  int ret = 0;
  char fname[COMMON_TEXT_SIZE];
  if (plugin_name == NULL)
    ret = -1;
  else {
    strcpy(fname, "plugins/");
    strcat(fname, plugin_name);
    strcat(fname, ".plug");
    ret = _load_plugin(fname);
  }

  return ret;
}

// void *_get_binary_func_internal(const char *name);

// int open_binary(const char *path) {
//   plugin_handle = dlopen(path, RTLD_NOW | RTLD_DEEPBIND);
//   if (plugin_handle == NULL) {
//     printf("dlopen error: %s\n", dlerror());
//     return -1;
//   }
//   return 0;
// }

// void *_get_binary_func_internal(const char *name) {
//   void *p = dlsym(plugin_handle, name);
//   if (p == NULL) {
//     printf("cannot open %s.\n", name);
//     exit(EXIT_FAILURE);
//   }
//   return p;
// }

// void *get_func(size_t pos) {
//   void *f = NULL;
//   char path[COMMON_TEXT_SIZE] = {0};

//  get_plugin_path(path, pos);
//  open_binary(path);
//  f = _get_binary_func_internal(list[pos].name);

//  return f;
//}

void *get_command(const char *command) {
  void *cmd = NULL;
  plugin_element *elem = NULL;
  elem = find_command(command);
  if (elem == NULL) {
    printf("cannot find \"%s\"\n", command);
    return NULL;
  }

  return cmd;
}

plugin_element *find_command(const char *command) {
  u_int cur_pos = _get_current_pos();
  for (u_int i = 0; i < cur_pos; ++i) {
    if (strcmp(list[i].desc.command, command) == 0) {
      return &list[i];
    }
  }
  return NULL;
}

bool is_command_binary(const plugin_element *elem) {}
