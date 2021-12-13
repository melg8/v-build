#include "config.h"

// work with files
#include <errno.h>

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "text_creation.h"
#include "text_processing.h"

static int config_fd;

void check_config(void) {
  if ((config_fd = open(CONFIG_FILE, O_RDWR)) == -1) {
    print_info_msg(INFO_MSG, "main config file do not exist.", YES);
    if (ask_yes_no("do you want to create it?") == YES) {
      // create_config();
    } else {
      print_info_msg(INFO_MSG, "entering to shell.", YES);
    }
  } else {
    close(config_fd);
  }
}

// void create_config(void) {
//   config_fd = creat(CONFIG_FILE, S_IRUSR | S_IWUSR);

//  if (config_fd == -1) {
//    char *str_err = strerror(errno);
//    print_info_msg(ERROR_MSG, str_err, YES);
//  } else {
//    char num[10];
//    char string[100];
//    int nbytes;

//    sprintf(num, "%d", config_fd);
//    strcpy(string, CONFIG_FILE);
//    strcat(string, " created.");
//    print_info_msg(INFO_MSG, string, YES);

//    int sz = sizeof(config_file_skeleton) / sizeof(config_file_skeleton[0]);

//    nbytes = write(config_fd, config_file_skeleton, sz);
//    if (nbytes == sz) {
//      print_info_msg(INFO_MSG, "Fill config file, then relaunch shell. Exit.",
//                     YES);
//      close(config_fd);
//      EXIT(EXIT_SUCCESS);
//    } else if (nbytes == -1) {
//      close(config_fd);
//      print_info_msg(ERROR_MSG, strerror(errno), YES);
//      EXIT(EXIT_FAILURE);
//    }
//  }
//}
