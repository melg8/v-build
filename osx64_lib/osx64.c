#include "osx64.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define V_BUILD_PKG_DIR_NAME "/packages"
#define V_BUILD_BUILD_DIR_NAME "/build_dir"
#define V_BUILD_PATCH_DIR_NAME "/patches"
#define V_BUILD_ARCHIVE_DIR_NAME "/archives"
#define V_BUILD_TGT_X86_64_NAME "x86_64-linux-gnu"
#define V_BUILD_TREE_X86_64_NAME "/tree_x86_64"
#define V_BUILD_TOOLS_X86_64_NAME "/tree_x86_64/tools"

#define COMMON_TEXT_SIZE 1024

void osx64_export_variables() {

  char V_BUILD_DIR_PATH[COMMON_TEXT_SIZE] = {0};
  char V_BUILD_DIR[COMMON_TEXT_SIZE] = {"V_BUILD_DIR"};

  if (getcwd(V_BUILD_DIR_PATH, COMMON_TEXT_SIZE) == NULL) {
    printf("Error exporting V_BUILD_DIR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    if (setenv(V_BUILD_DIR, V_BUILD_DIR_PATH, 1) != 0) {
      printf("setenv error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  char V_BUILD_PKG_DIR[COMMON_TEXT_SIZE] = {0};
  strcat(V_BUILD_PKG_DIR, V_BUILD_DIR_PATH);
  strcat(V_BUILD_PKG_DIR, V_BUILD_PKG_DIR_NAME);
  if (setenv("V_BUILD_PKG_DIR", V_BUILD_PKG_DIR, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char V_BUILD_BUILD_DIR[COMMON_TEXT_SIZE] = {0};
  strcat(V_BUILD_BUILD_DIR, V_BUILD_DIR_PATH);
  strcat(V_BUILD_BUILD_DIR, V_BUILD_BUILD_DIR_NAME);
  if (setenv("V_BUILD_BUILD_DIR", V_BUILD_BUILD_DIR, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char V_BUILD_PATCH_DIR[COMMON_TEXT_SIZE] = {0};
  strcat(V_BUILD_PATCH_DIR, V_BUILD_DIR_PATH);
  strcat(V_BUILD_PATCH_DIR, V_BUILD_PATCH_DIR_NAME);
  if (setenv("V_BUILD_PATCH_DIR", V_BUILD_PATCH_DIR, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char V_BUILD_ARCHIVE_DIR[COMMON_TEXT_SIZE] = {0};
  strcat(V_BUILD_ARCHIVE_DIR, V_BUILD_DIR_PATH);
  strcat(V_BUILD_ARCHIVE_DIR, V_BUILD_ARCHIVE_DIR_NAME);
  if (setenv("V_BUILD_ARCHIVE_DIR", V_BUILD_ARCHIVE_DIR, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char V_BUILD_TGT_X86_64[COMMON_TEXT_SIZE] = {0};
  strcat(V_BUILD_TGT_X86_64, V_BUILD_TGT_X86_64_NAME);
  if (setenv("V_BUILD_TGT_X86_64", V_BUILD_TGT_X86_64, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char V_BUILD_TREE_X86_64[COMMON_TEXT_SIZE] = {0};
  strcat(V_BUILD_TREE_X86_64, V_BUILD_DIR_PATH);
  strcat(V_BUILD_TREE_X86_64, V_BUILD_TREE_X86_64_NAME);
  if (setenv("V_BUILD_TREE_X86_64", V_BUILD_TREE_X86_64, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  char V_BUILD_TOOLS_X86_64[COMMON_TEXT_SIZE] = {0};
  strcat(V_BUILD_TOOLS_X86_64, V_BUILD_DIR_PATH);
  strcat(V_BUILD_TOOLS_X86_64, V_BUILD_TOOLS_X86_64_NAME);
  if (setenv("V_BUILD_TOOLS_X86_64", V_BUILD_TOOLS_X86_64, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("exported.\n");
}

void osx64_export_linux_kernel(const char *path) {
  char V_BUILD_KERNEL_X86_64[COMMON_TEXT_SIZE] = {"V_BUILD_KERNEL_X86_64"};

  DIR *kernel_dir = opendir(path);

  if (kernel_dir == NULL) {
    printf("cannot open kernel dir: %s\n", strerror(errno));
    printf("maybe it doesn't exist?\n");
  } else {
    closedir(kernel_dir);
    if (setenv(V_BUILD_KERNEL_X86_64, path, 1) != 0) {
      printf("setenv error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    } else {
      printf("exported.\n");
    }
  }
}
