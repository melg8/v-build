#ifndef TEXT_CREATION_H
#define TEXT_CREATION_H

#include "os_global.h"

#define SIMPLE_CMD 0
#define COMPOSITE_CMD 1

// commands list:
typedef struct cmd_triplet {
  char *full_name;
  char *short_name;
  char *desc;
  int property; // property holds whether composite or simple value
} cmd_triplet;

static const cmd_triplet help_cmds[] = {
    {"help", "h", "help message", SIMPLE_CMD},
    {"status", "s", "builder status", COMPOSITE_CMD},
    {"build", "b", "build os", COMPOSITE_CMD},
    {"configure", "cfg", "edit preparation file", COMPOSITE_CMD},
    {"quit", "q", "exit program", SIMPLE_CMD},
    {"view_config", "vc", "view configuration file", SIMPLE_CMD},
    {"clear", "c", "clear screen", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD},
    {"empty", "empty", "empty", SIMPLE_CMD}};

// generate full error message, need to be freed.
char *generate_error_string(const char *text);
char *generate_help_string();

#endif // TEXT_CREATION_H
