#include "osx64.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//    "V_BUILD_DIR" +
//    "V_BUILD_PKG_DIR" +
//    "V_BUILD_SYSTEM" +
//    "V_BUILD_BUILD_DIR" +
//    "V_BUILD_PATCH_DIR" +
//    "V_BUILD_ARCHIVE_DIR" +
//    "2"
//    "V_BUILD_TGT_X86_64" = x86_64-linux-gnu +
//    "V_BUILD_TREE_X86_64" = tree_x86_64 +
//    "V_BUILD_TOOLS_X86_64" = tree_x86_64/tools +
//    "3"
//    "LINUX_KERNEL"

#define COMMON_TEXT_SIZE 1024

static size_t idx = 0;

static char vars[COMMON_TEXT_SIZE][COMMON_TEXT_SIZE] = {0};

void export_variables() {

  char V_BUILD_DIR_PATH[COMMON_TEXT_SIZE] = {0};
  char V_BUILD_DIR[COMMON_TEXT_SIZE] = {"V_BUILD_DIR"};

  if (getcwd(V_BUILD_DIR_PATH, COMMON_TEXT_SIZE) == NULL) {
    printf("Error exporting V_BUILD_DIR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    strcat(V_BUILD_DIR, "=");
    strcat(V_BUILD_DIR, V_BUILD_DIR_PATH);
    strcpy(vars[idx], V_BUILD_DIR);
    ++idx;
  }

  char V_BUILD_PKG_DIR[COMMON_TEXT_SIZE] = {"V_BUILD_PKG_DIR="};
  strcat(V_BUILD_PKG_DIR, V_BUILD_DIR_PATH);
  strcat(V_BUILD_PKG_DIR, "/");
  strcat(V_BUILD_PKG_DIR, "packages");
  strcpy(vars[idx], V_BUILD_PKG_DIR);
  ++idx;

  char V_BUILD_SYSTEM[COMMON_TEXT_SIZE] = {"V_BUILD_SYSTEM="};
  strcat(V_BUILD_SYSTEM, V_BUILD_DIR_PATH);
  strcat(V_BUILD_SYSTEM, "/");
  strcat(V_BUILD_SYSTEM, "system");
  strcpy(vars[idx], V_BUILD_SYSTEM);
  ++idx;

  char V_BUILD_BUILD_DIR[COMMON_TEXT_SIZE] = {"V_BUILD_BUILD_DIR="};
  strcat(V_BUILD_BUILD_DIR, V_BUILD_DIR_PATH);
  strcat(V_BUILD_BUILD_DIR, "/");
  strcat(V_BUILD_BUILD_DIR, "build_dir");
  strcpy(vars[idx], V_BUILD_BUILD_DIR);
  ++idx;

  char V_BUILD_PATCH_DIR[COMMON_TEXT_SIZE] = {"V_BUILD_PATCH_DIR="};
  strcat(V_BUILD_PATCH_DIR, V_BUILD_DIR_PATH);
  strcat(V_BUILD_PATCH_DIR, "/");
  strcat(V_BUILD_PATCH_DIR, "patches");
  strcpy(vars[idx], V_BUILD_PATCH_DIR);
  ++idx;

  char V_BUILD_ARCHIVE_DIR[COMMON_TEXT_SIZE] = {"V_BUILD_ARCHIVE_DIR="};
  strcat(V_BUILD_ARCHIVE_DIR, V_BUILD_DIR_PATH);
  strcat(V_BUILD_ARCHIVE_DIR, "/");
  strcat(V_BUILD_ARCHIVE_DIR, "archives");
  strcpy(vars[idx], V_BUILD_ARCHIVE_DIR);
  ++idx;

  char V_BUILD_TGT_X86_64[COMMON_TEXT_SIZE] = {"V_BUILD_TGT_X86_64="};
  strcat(V_BUILD_TGT_X86_64, "x86_64-linux-gnu");
  strcpy(vars[idx], V_BUILD_TGT_X86_64);
  ++idx;

  char V_BUILD_TREE_X86_64[COMMON_TEXT_SIZE] = {"V_BUILD_TREE_X86_64="};
  strcat(V_BUILD_TREE_X86_64, V_BUILD_DIR_PATH);
  strcat(V_BUILD_TREE_X86_64, "/");
  strcat(V_BUILD_TREE_X86_64, "tree_x86_64");
  strcpy(vars[idx], V_BUILD_TREE_X86_64);
  ++idx;

  char V_BUILD_TOOLS_X86_64[COMMON_TEXT_SIZE] = {"V_BUILD_TOOLS_X86_64="};
  strcat(V_BUILD_TOOLS_X86_64, V_BUILD_DIR_PATH);
  strcat(V_BUILD_TREE_X86_64, "/");
  strcat(V_BUILD_TOOLS_X86_64, "tree_x86_64/tools");
  strcpy(vars[idx], V_BUILD_TOOLS_X86_64);
  ++idx;

  for (size_t i = 0; i < idx; ++i) {
    if (putenv(vars[i]) != 0) {
      printf("putenv error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  system("env | sort | grep V_BUILD");
}
