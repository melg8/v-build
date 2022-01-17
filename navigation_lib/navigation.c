#include "navigation.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void ls(const char *path) {

  //  DIR *d = NULL;
  //  struct dirent *dir = NULL;
  //  struct stat st;

  //  if ((d = opendir(path)) == NULL) {
  //    printf("%s\n", strerror(errno));
  //    return -1;
  //  }

  //  while ((dir = readdir(d)) != NULL) {
  //    printf("file: %s\n", dir->d_name);
  //    int ret = stat(dir->d_name, &st);
  //    if (ret == -1) {
  //      printf("%s\n", strerror(errno));
  //      continue;
  //    }
  //    printf("%-10lu %s %s\n", st.st_size / 1024, "kb", dir->d_name);
  //  }

  //  closedir(d);

  char lscmd[1024] = {0};
  strcpy(lscmd, "ls ");
  strcat(lscmd, path);
  strcat(lscmd, " ");
  strcat(lscmd, "-lah --color=auto");

  system(lscmd);
}

void pwd() { system("pwd"); }

int cd(const char *path) {
  int ret = chdir(path);

  if (ret != 0) {
    printf("%s\n", strerror(errno));
  }

  return ret;
}
