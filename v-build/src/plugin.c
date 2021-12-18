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

// void *plugin_handle = NULL;

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
