#ifndef TEXT_CREATION_H
#define TEXT_CREATION_H

#include "text_global.h"

// commands list:
typedef struct cmd_bunch {
  char *full_name;
  char *short_name;
  char *desc;
} cmd_bunch;

static const cmd_bunch help_cmds[] = {
    {"help", "h", "help message"},
    {"clear", "c", "clear screen"},
    {"quit", "q", "exit program"},
    {"plugins", "p", "view all plugins, located in plugins dir"},
    {"load", "l", "load plugin from plugins dir"}};

char *generate_help_string();

#endif // TEXT_CREATION_H
