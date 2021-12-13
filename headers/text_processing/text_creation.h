#ifndef TEXT_CREATION_H
#define TEXT_CREATION_H

#include "os_global.h"

#define SIMPLE 0
#define COMPOSITE 1

// commands list:
typedef struct cmd_bunch {
  char *full_name;
  char *short_name;
  char *desc;
  int property; // property holds whether composite or simple value
} cmd_bunch;

static const cmd_bunch help_cmds[] = {
    {"help", "h", "help message", SIMPLE},
    {"status", "s", "builder status", COMPOSITE},
    {"clear", "c", "clear screen", SIMPLE},
    {"quit", "q", "exit program", SIMPLE},
    {"view plugins", "vp", "view available plugins", SIMPLE},
    {"load plugin", "lp", "load you plugin", SIMPLE},
    {"reload plugins", "rp", "reload plugins dir", SIMPLE},
    {"empty", "empty", "empty", SIMPLE}};

char *generate_help_string();

#endif // TEXT_CREATION_H
