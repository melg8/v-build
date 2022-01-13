#ifndef LINE_ARGS_PARSER_H
#define LINE_ARGS_PARSER_H

#include <stdbool.h>

#include "bin_parser.h"
#include "plugin.h"
#include "plugin_parser.h"

char *get_command_from_line(const char *restrict cmd_line);
bool fill_line_args(const plugin_element *restrict elem);

#endif // LINE_ARGS_PARSER_H
