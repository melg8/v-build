#include "build_menu.h"

#include <stdio.h>
#include <string.h>

#include "bin_exec.h"
#include "column_args_parser.h"
#include "io.h"
#include "line_args_parser.h"
#include "script_exec.h"
#include "shell_helper.h"
#include "subshell.h"
#include "v_build_global.h"

static void run_internal(const char *cmd) {
  plugin_element *elem = NULL;
  elem = find_element_by_command(get_command_from_line(cmd));
  run_plugin(elem);
  reset_user_args();
}

static void unknow_answer() {
  print_info_msg(ERROR_MSG, "unknown answer", YES);
}

bool is_build_menu(const char *cmd) {
  if (strcmp(cmd, "build") == 0) {
    return true;
  }
  return false;
}

void run_build_menu() {
  char choice[COMMON_TEXT_SIZE] = {};

  print_info_msg(COMPLETE, "inside build menu", YES);
  print_info_msg("",
                 "1. build toolchain\n"
                 "2. modify toolchain",
                 YES);

  strcpy(choice, get_shell_input("choice: "));

  if (strcmp(choice, "1") == 0) {
    run_build_cmd();
  } else {
    unknow_answer();
  }
}

void run_build_cmd() {
  char choice[COMMON_TEXT_SIZE] = {};
  print_info_msg("\nplatform:\n",
                 "1. x86_64\n"
                 "2. arm64",
                 YES);
  strcpy(choice, get_shell_input("choice: "));

  if (strcmp(choice, "1") == 0) {
    prepare_toolchain_x86_64();
  } else {
    unknow_answer();
  }
}

void prepare_toolchain_x86_64() {

  char choice[COMMON_TEXT_SIZE] = {};

  print_info_msg(INFO_MSG,
                 "open new terminal and copy linux kernel folder here, name "
                 "should start with linux*",
                 YES);
  get_shell_input("press enter after");

  run_internal("ls .");

  // pipe stream
  FILE *pipe = popen("readlink -f `ls . | grep linux`", "r");
  char buf[COMMON_TEXT_SIZE] = {};
  if (pipe) {
    while (fgets(buf, COMMON_TEXT_SIZE, pipe)) {
      print_info_msg("\nkernel found: ", buf, YES);
    }
  }
  pclose(pipe);

  print_info_msg(QUESTION, "\nis it correct?\n"
                           "1. Yes\n"
                           "2. No\n");

  strcpy(choice, get_shell_input("answer: "));

  if (strcmp(choice, "1") == 0) {
    char temp[COMMON_TEXT_SIZE] = "osx64_export_linux_kernel";
    strcat(temp, " ");
    strcat(temp, buf);
    temp[strcspn(temp, "\n")] = 0;

    run_internal(temp);
    run_internal("osx64_set_machine_name");
    run_internal("osx64_export_variables");
    run_internal("osx64_create_all_dirs");
    run_internal("osx64_construct_tree");
    run_internal("osx64_check_variables");
    run_internal("osx64_check_host");

    // check host before build
    print_info_msg(INFO_MSG,
                   "check your machine before building, everything is ok?\n"
                   "1. Yes\n"
                   "2. No",
                   YES);
    strcpy(choice, get_shell_input("answer: "));

    if (strcmp(choice, "1") == 0) {
      // start_build
      start_build_toolchain_x86_64();
    } else if (strcmp(choice, "2") == 0) {
      return;
    } else {
      unknow_answer();
    }

  } else {
    unknow_answer();
  }
}

void start_build_toolchain_x86_64() {
  run_internal("osx64_download");
  run_internal("osx64_extract");
  run_internal("osx64_binutils_pass_1");
  run_internal("osx64_gcc_pass_1");
  run_internal("osx64_install_kernel_headers");
  run_internal("osx64_glibc");
  run_internal("osx64_gcc_mkheaders");
  run_internal("osx64_libstd_cpp_pass_1");
  run_internal("osx64_sysutils");
  run_internal("osx64_binutils_pass_2");
  run_internal("osx64_gcc_pass_2");
  run_internal("osx64_copy_kernel_into_tree");
}
