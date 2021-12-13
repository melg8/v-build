#include "config.h"

// work with files
#include <errno.h>

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "text_processing.h"

void check_config() {
  int fd;
  if ((fd = open(CONFIG_FILE, O_RDWR)) == -1) {
    print_info_msg(INFO_MSG, "main config file do not exist.", YES);
    if (ask_yes_no("do you want to create it?") == YES) {
      create_config();
    } else {
      close(fd);
      print_info_msg(INFO_MSG, "entering to shell.", YES);
    }
  }
}

void create_config() {
  int fd = creat(CONFIG_FILE, S_IRUSR | S_IWUSR);

  if (fd == -1) {
    char *str_err = strerror(errno);
    print_info_msg(ERROR_MSG, str_err, YES);
  } else {
    char num[10];
    char string[100];

    sprintf(num, "%d", fd);
    strcpy(string, CONFIG_FILE);
    strcat(string, " file created, fd = ");
    strcat(string, num);
    print_info_msg(INFO_MSG, string, YES);
  }
}
