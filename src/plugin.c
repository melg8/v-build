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

#include "text_creation.h"
#include "text_processing.h"

void check_common_plugin() {
  char fullpath[COMMON_TEXT_SIZE];
  char *cur_pwd = getenv("PWD");
  struct stat st;

  if (cur_pwd == NULL) {
    print_info_msg(ERROR_MSG, "cannot find PWD env variable. (plugin.h)", YES);
  }

  strcpy(fullpath, cur_pwd);
  strcat(fullpath, "/");
  strcat(fullpath, COMMON_PLUGIN);

  if (stat(fullpath, &st) == -1) {
    char err[COMMON_TEXT_SIZE];
    strcpy(err, fullpath);
    strcat(err, ", ");
    strcat(err, strerror(errno));
    print_info_msg(ERROR_MSG, err, YES);
    EXIT(EXIT_FAILURE);
  }

  if (!S_ISREG(st.st_mode)) {
    print_info_msg(ERROR_MSG, "common plugin is not a regular file, exit.",
                   YES);
    EXIT(EXIT_FAILURE);
  }
}
