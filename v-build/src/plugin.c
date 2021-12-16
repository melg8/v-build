#include "plugin.h"

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "plugin_parser.h"
//#include "text_creation.h"
//#include "text_processing.h"

static char *cur_pwd = NULL;
static char full_plugin_path[COMMON_TEXT_SIZE];

int _check_common_plugin();

void load_common_plugin() {
  if (_check_common_plugin() != 0) {
    printf("common plugin not loaded\n");
    return;
  }
  if (load_plugin(full_plugin_path) != 0) {
    printf("common plugin not loaded\n");
    return;
  }
  printf("common plugin loaded\n\n");

  for (int i = 0; i < 3; ++i) {
    printf("name: %s\n", plugin_list[i].plugin_name);
    printf("type: %s\n", plugin_list[i].type);
    printf("alias: %s\n", plugin_list[i].alias);
    printf("dir: %s\n", plugin_list[i].dir);
    printf("exec: %s\n", plugin_list[i].exec);
    printf("desc: %s\n\n", plugin_list[i].desc);
  }
}

int _check_common_plugin() {
  cur_pwd = getenv("PWD");
  struct stat st;

  if (cur_pwd == NULL) {
    // print_info_msg(ERROR_MSG, "cannot find PWD env variable. (plugin.h)",
    // YES);
  }

  strcpy(full_plugin_path, cur_pwd);
  strcat(full_plugin_path, "/");
  strcat(full_plugin_path, COMMON_PLUGIN);

  if (stat(full_plugin_path, &st) == -1) {
    char err[COMMON_TEXT_SIZE];
    strcpy(err, full_plugin_path);
    strcat(err, ", ");
    strcat(err, strerror(errno));
    // print_info_msg(ERROR_MSG, err, YES);
    EXIT(EXIT_FAILURE);
  }

  if (!S_ISREG(st.st_mode)) {
    // print_info_msg(ERROR_MSG, "common plugin is not a regular file, exit.",
    // YES);
    EXIT(EXIT_FAILURE);
  }
  return 0;
}
