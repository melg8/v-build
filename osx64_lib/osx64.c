#include "osx64.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//    "V_BUILD_DIR"
//    "V_BUILD_PKG_DIR"
//    "V_BUILD_SYSTEM"
//    "V_BUILD_BUILD_DIR"
//    "V_BUILD_PATCH_DIR"
//    "V_BUILD_ARCHIVE_DIR"
//    "2"
//    "V_BUILD_TGT_X86_64"
//    "V_BUILD_TREE_X86_64"
//    "V_BUILD_TOOLS_X86_64"
//    "V_BUILD_PRIVATE_X86_64"
//    "3"
//    "LINUX_KERNEL"

#define COMMON_TEXT_SIZE 1024

static size_t idx = 0;

static char vars[COMMON_TEXT_SIZE][COMMON_TEXT_SIZE] = {0};

void export_variables() {

  char V_BUILD_DIR[COMMON_TEXT_SIZE] = {0};

  if (getcwd(V_BUILD_DIR, COMMON_TEXT_SIZE) == NULL) {
    printf("Error exporting V_BUILD_DIR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  } else {
    strcpy(vars[idx], V_BUILD_DIR);
    ++idx;
  }
}
