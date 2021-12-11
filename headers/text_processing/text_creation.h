#ifndef TEXT_CREATION_H
#define TEXT_CREATION_H

#include "os_global.h"

// commands list:
typedef struct cmd_triplet {
  char *full_name;
  char *short_name;
  char *desc;
} cmd_triplet;

static cmd_triplet cmds[] = {{"help", "h", "help message"},
                             {"status", "s", "builder status"}};

// generate full error message, need to be freed.
char *generate_error_string(const char *text);
char *generate_help_string();

#endif // TEXT_CREATION_H
