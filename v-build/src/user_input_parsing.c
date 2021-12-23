#include "user_input_parsing.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "io.h"

char user_args_etalon[ARGS_COUNT][COMMON_TEXT_SIZE] = {0};
char user_input_args[ARGS_COUNT][COMMON_TEXT_SIZE] = {0};
size_t cnt = 0;
bool is_input_correct = false;
bool is_has_args = false;

void _print_pre_input_text(const char *arg_type);

void parse_user_plugin_input(const char *cmd) {
  plugin_element *elem = find_element_by_command(cmd);

  if (elem == NULL) {
    print_info_msg(ERROR_MSG, "Strange behaviour, command not found", YES);
    return;
  }

  if (is_elem_binary(elem)) {

    voidfunc f = get_binary_function(cmd);

    if (is_func_has_args(elem)) {
      reset_user_args();

      char *str = elem->descriptor.args;

      // get etalon func args and place them into user_args_etalon
      parse_args(str);

      while (!is_input_correct) {
        get_func_args();
      }
    } else {
      // run without args
    }
  }
}

void parse_args(const char *elem_args) {
  char copy[COMMON_TEXT_SIZE];
  strcpy(copy, elem_args);
  char delim[] = ",";
  char *p = NULL;

  p = strtok(copy, delim);

  // find all args
  while (p != NULL) {
    strcpy(user_args_etalon[cnt], p);
    p = strtok(NULL, delim);
    cnt++;
  }

  // remove whitespaces in args, if any exists
  for (size_t i = 0; i < cnt; ++i) {
    char temp[COMMON_TEXT_SIZE] = {0};
    strcpy(temp, user_args_etalon[i]);
    size_t spnz = strspn(temp, " ");
    strcpy(user_args_etalon[i], temp + spnz);
  }

  for (size_t i = 0; i < cnt; ++i) {
    print_info_msg("etalon: ", user_args_etalon[i], YES);
  }
}

bool is_func_has_args(const plugin_element *elem) {
  is_has_args = strcmp(elem->descriptor.args, NO_ARGS) != 0;
  return is_has_args;
}

void get_func_args() {
  char arg_type_must_be[COMMON_TEXT_SIZE] = {0};

  if (cnt == 0)
    return;

input:
  for (size_t i = 0; i < cnt; ++i) {

    _print_pre_input_text(user_args_etalon[i]);

    char *arg_value = get_input(arg_type_must_be);
    strcpy(user_input_args[i], arg_value);

    memset(arg_type_must_be, 0, sizeof(arg_type_must_be));
  }

  if (!is_args_ok()) {
    print_info_msg(ERROR_MSG, "arguments incorrect", YES);
    goto input;
  }

  is_input_correct = true;
}

bool is_args_ok() {

  bool is_ok = true;

  for (size_t i = 0; i < cnt; ++i) {
    if (is_has_args && (strlen(user_input_args[i]) == 0)) {
      print_info_msg(ERROR_MSG, "length of arg = 0!", YES);
      is_ok = false;
    }
    if ((strcmp(user_args_etalon[i], IS_VALUE_INT) == 0)) {
      if (!is_arg_numeric(user_input_args[i])) {
        char temp[COMMON_TEXT_SIZE];
        strcpy(temp, "argument incorrect, it must be \"");
        strcat(temp, user_args_etalon[i]);
        strcat(temp, "\"");
        strcat(temp, ", but you have entered \"");
        strcat(temp, user_input_args[i]);
        strcat(temp, "\"");
        print_info_msg(ERROR_MSG, temp, YES);
        is_ok = false;
      }
    }
  }
  return is_ok;
}

void reset_user_args() {
  // reset input data
  memset(user_args_etalon, 0, sizeof(user_args_etalon));
  memset(user_input_args, 0, sizeof(user_input_args));
  is_input_correct = false;
  is_has_args = false;
  cnt = 0;
}

void _print_pre_input_text(const char *arg_type) {
  char text[COMMON_TEXT_SIZE] = "arg ";
  strcat(text, arg_type);
  strcat(text, ": ");
  print_msg(text, 0);
}

bool is_arg_numeric(const char *arg) {
  for (size_t j = 0; j < strlen(arg); ++j) {
    if (isdigit(arg[j]) == 0) {
      return false;
    }
  }
  printf("\n");
  return true;
}
