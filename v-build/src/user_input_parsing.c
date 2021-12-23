#include "user_input_parsing.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "io.h"

char user_args_etalon[ARGS_COUNT][COMMON_TEXT_SIZE] = {0};
char user_input_args[ARGS_COUNT][COMMON_TEXT_SIZE] = {0};
size_t _cnt = 0;
bool _is_input_correct = false;
bool _is_has_args = false;
bool _is_args_ok = true;

//                      INNER

void _print_pre_input_text(const char *arg_type) {
  char text[COMMON_TEXT_SIZE] = "arg ";
  strcat(text, arg_type);
  strcat(text, ": ");
  print_msg(text, 0);
}

//                      END

void parse_user_plugin_input(const char *cmd) {
  plugin_element *elem = find_element_by_command(cmd);

  if (elem == NULL) {
    print_info_msg(ERROR_MSG, "Strange behaviour, command not found", YES);
    return;
  }

  if (is_elem_binary(elem)) {

    // voidfunc f = get_binary_function(cmd);

    reset_user_args();
    if (is_func_has_args(elem)) {

      char *str = elem->descriptor.args;

      // get etalon func args and place them into user_args_etalon
      parse_args(str);

      while (!_is_input_correct) {
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
    strcpy(user_args_etalon[_cnt], p);
    p = strtok(NULL, delim);
    _cnt++;
  }

  // remove whitespaces in args, if any exists
  for (size_t i = 0; i < _cnt; ++i) {
    char temp[COMMON_TEXT_SIZE] = {0};
    strcpy(temp, user_args_etalon[i]);
    size_t spnz = strspn(temp, " ");
    strcpy(user_args_etalon[i], temp + spnz);
  }
}

bool is_func_has_args(const plugin_element *elem) {
  _is_has_args = strcmp(elem->descriptor.args, NO_ARGS) != 0;
  return _is_has_args;
}

void get_func_args() {
  char arg_type_must_be[COMMON_TEXT_SIZE] = {0};

  if (_cnt == 0)
    return;

input:
  for (size_t i = 0; i < _cnt; ++i) {

    _print_pre_input_text(user_args_etalon[i]);

    char *arg_value = get_input(arg_type_must_be);
    strcpy(user_input_args[i], arg_value);

    memset(arg_type_must_be, 0, sizeof(arg_type_must_be));
  }

  if (!is_args_ok()) {
    goto input;
  }

  _is_input_correct = true;
}

bool is_args_ok() {

  bool temp = true;

  for (size_t i = 0; i < _cnt; ++i) {

    if (is_empty_arg(user_input_args[i])) {
      print_incorrect_expected_values(i, user_args_etalon[i],
                                      user_input_args[i]);
      temp = false;
      break;
    }

    if (is_arg_must_be_numeric(user_args_etalon[i])) {
      if (!is_arg_digits(user_input_args[i])) {
        print_incorrect_expected_values(i, user_args_etalon[i],
                                        user_input_args[i]);
        temp = false;
        break;
      }
    }
  }
  _is_args_ok = temp;
  return _is_args_ok;
}

bool is_arg_digits(const char *entered) {

  for (size_t j = 0; j < strlen(entered); ++j) {
    if (isdigit(entered[j]) == 0) {
      return false;
    }
  }

  return true;
}

bool is_empty_arg(const char *entered) {
  return _is_has_args && (strlen(entered) == 0);
}

void reset_user_args() {
  // reset input data
  memset(user_args_etalon, 0, sizeof(user_args_etalon));
  memset(user_input_args, 0, sizeof(user_input_args));
  _is_input_correct = false;
  _is_has_args = false;
  _cnt = 0;
  _is_args_ok = true;
}

void print_incorrect_expected_values(size_t cur_cnt, const char *expected,
                                     const char *entered) {
  char temp[COMMON_TEXT_SIZE];
  char value[10] = {0};
  strcpy(temp, "arg(");
  sprintf(value, "%lo", cur_cnt);
  strcat(temp, value);
  strcat(temp, "), ");
  strcat(temp, "expected type: \"");
  strcat(temp, expected);
  strcat(temp, "\", ");
  strcat(temp, "entered value: \"");
  strcat(temp, entered);
  strcat(temp, "\"");
  print_info_msg(ERROR_MSG, temp, YES);
}

bool is_arg_must_be_numeric(const char *expected) {
  if ((strcmp(expected, IS_VALUE_INT) == 0)) {
    return true;
  }
  return false;
}
