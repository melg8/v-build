#include "arm64.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define V_BUILD_ARM64_FLOAT_DEF "hard"
#define V_BUILD_ARM64_FPU_DEF "vfpv4"
#define V_BUILD_ARM64_HOST_DEF "x86_64-cross-linux-gnu"
#define V_BUILD_ARM64_TGT_DEF "arm-linux-musleabihf"
#define V_BUILD_ARM64_ARCH_DEF "arm"
#define V_BUILD_ARM64_ARM_ARCH_DEF "armv8-a"

#define V_BUILD_PKG_DIR_DEF "/tree_arm64/packages"
#define V_BUILD_PATCH_DIR_DEF "/patches"
#define V_BUILD_ARCHIVE_DIR_DEF "/archives"

#define V_BUILD_TREE_ARM64_DEF "/tree_arm64"
#define V_BUILD_TOOLS_ARM64_DEF "/tree_arm64/tools"

#define COMMON_TEXT_SIZE 1024

static char V_BUILD_DIR_PATH[COMMON_TEXT_SIZE] = {0};

static int export_tgt() {
  char V_BUILD_TGT_ARM64[COMMON_TEXT_SIZE] = {0};

  strcpy(V_BUILD_TGT_ARM64, V_BUILD_ARM64_TGT_DEF);
  if (setenv("V_BUILD_TGT_ARM64", V_BUILD_TGT_ARM64, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}

static void export_var(const char *varname, const char *varvalue) {
  char var[COMMON_TEXT_SIZE] = {0};
  strcpy(var, V_BUILD_DIR_PATH);
  strcat(var, varvalue);
  if (setenv(varname, var, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
}

void arm64_export_variables() {

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

  export_tgt();

  export_var("V_BUILD_PKG_DIR", V_BUILD_PKG_DIR_DEF);
  export_var("V_BUILD_PATCH_DIR", V_BUILD_PATCH_DIR_DEF);
  export_var("V_BUILD_ARCHIVE_DIR", V_BUILD_ARCHIVE_DIR_DEF);
  export_var("V_BUILD_TREE_ARM64", V_BUILD_TREE_ARM64_DEF);
  export_var("V_BUILD_TOOLS_ARM64", V_BUILD_TOOLS_ARM64_DEF);

  char temp[COMMON_TEXT_SIZE] = {0};
  strcpy(temp, getenv("V_BUILD_TOOLS_ARM64"));

  char NEW_PATH[COMMON_TEXT_SIZE] = {0};
  //$LFS/tools/bin:
  strcpy(NEW_PATH, temp);
  strcat(NEW_PATH, "/bin");
  strcat(NEW_PATH, ":/usr/bin");

  if (setenv("PATH", NEW_PATH, 1) != 0) {
    printf("setenv error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("exported.\n");
}

void arm64_export_linux_kernel(const char *path) {
  char V_BUILD_KERNEL_ARM64[COMMON_TEXT_SIZE] = {"V_BUILD_KERNEL_ARM64"};

  DIR *kernel_dir = opendir(path);

  if (kernel_dir == NULL) {
    printf("cannot open kernel dir: %s\n", strerror(errno));
    printf("maybe it doesn't exist?\n");
  } else {
    closedir(kernel_dir);
    if (setenv(V_BUILD_KERNEL_ARM64, path, 1) != 0) {
      printf("setenv error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    } else {
      printf("exported.\n");
    }
  }
}
