#ifndef LINE_ARGS_PARSER_H
#define LINE_ARGS_PARSER_H

#include "bin_parser.h"
#include "plugin.h"

char *get_command_from_line(const char *restrict cmd_line);
void fill_line_args();

#endif // LINE_ARGS_PARSER_H
