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
    {"clear", "c", "clear screen", SIMPLE},
    {"quit", "q", "exit program", SIMPLE},
    {"view plugins", "vp", "view available plugins", SIMPLE},
    {"load plugin", "lp", "load you plugin", SIMPLE},
    {"reload plugins", "rp", "reload plugins dir", SIMPLE},
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

// static const char config_file_skeleton[] = {
//     "# the root of build dir\n"
//     "V_BUILD_DIR=\n"
//     "\n"
//     "# directory for package source codes\n"
//     "V_BUILD_PKG_DIR=\n"
//     "\n"
//     "# plugin directory root\n"
//     "V_BUILD_PLUGIN=\n"
//     "\n"
//     "# directory for package builds\n"
//     "V_BUILD_BUILD_DIR=\n"
//     "\n"
//     "# archive directory\n"
//     "V_BUILD_ARCHIVE_DIR=\n"};

#endif // TEXT_CREATION_H
