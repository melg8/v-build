#ifndef TEXT_CREATION_H
#define TEXT_CREATION_H

#include "os_global.h"

#define SIMPLE 0
#define COMPOSITE 1

// commands list:
typedef struct cmd_triplet {
  char *full_name;
  char *short_name;
  char *desc;
  int property; // property holds whether composite or simple value
} cmd_triplet;

static const cmd_triplet help_cmds[] = {
    {"help", "h", "help message", SIMPLE},
    {"status", "s", "builder status", COMPOSITE},
    {"build", "b", "build os", COMPOSITE},
    {"configure", "cfg", "edit main configuration file", COMPOSITE},
    {"view config", "vc", "view main configuration file", SIMPLE},
    {"quit", "q", "exit program", SIMPLE},
    {"clear", "c", "clear screen", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE},
    {"empty", "empty", "empty", SIMPLE}};

char *generate_help_string();

#endif // TEXT_CREATION_H
