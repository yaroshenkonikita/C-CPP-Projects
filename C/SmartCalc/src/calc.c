#include "calc.h"

int s21_calc(char *input_string, double *out, double x) {
  int res = strlen(input_string) < 256 ? 0 : 2;
  if (!res) {
    char new_string[255] = {0};
    check_unar(input_string, new_string);
    double buff = 0.0;
    res = calc_work(new_string, &buff, x);
    if (!res) {
      if (buff < 1e-7 && buff > -1e-7) {
        buff = 0.0;
      }
      *out = buff;
    }
  }
  return res;
}

int calc_work(char *new_string, double *out, double x) {
  num_array num_arr = {{0}, -1};
  operator_string string_oper = {{0}, -1, 0};
  int res = 0, index = strlen(new_string);
  for (int i = 0; i < index && !res;) {
    if (new_string[i] >= '0' && new_string[i] <= '9') {
      double buf_num = 0.0;
      res = string_to_num(new_string, &i, &buf_num);
      if (!res) {
        res = push_num_array(&num_arr, buf_num);
      }
    } else if (new_string[i] == 'p') {
      i++;
    } else if (new_string[i] == 'x') {
      res = push_num_array(&num_arr, x);
      i++;
    } else if (new_string[i] == 'f') {
      res = push_num_array(&num_arr, 3.14159265358979323846);
      i++;
    } else if (new_string[i] == 'e') {
      res = push_num_array(&num_arr, 2.71828182845904523536);
      i++;
    } else {
      if (((get_prior(new_string[i]) == 5 &&
            (string_oper.priority == 5 || string_oper.priority == 8)) ||
           string_oper.top_operatoration == -1 ||
           get_prior(new_string[i]) > string_oper.priority ||
           new_string[i] == '(') &&
          new_string[i] != ')') {
        res = push_operator_string(&string_oper, new_string[i]);
        i++;
      } else {
        stack_processing(&string_oper, &num_arr, &res, new_string[i]);
        i++;
      }
    }
  }
  stack_processing(&string_oper, &num_arr, &res, 0);
  if (!res) {
    *out = pop_num_array(&num_arr);
  }
  if (*out != *out) {
    res = 12;
  }
  return res;
}

void stack_processing(operator_string *string_func, num_array *num_arr,
                      int *err, char src) {
  while ((((src == ')' && get_operator_string(*string_func) != '(') ||
           (src != ')' && (get_prior(src) <= string_func->priority))) ||
          (!src)) &&
         (get_operator_string(*string_func) != 127 && !*err)) {
    int priority = string_func->priority;
    char char_1 = pop_operator_string(string_func);
    double res = 0.0;
    if (priority != 5 && priority != 8) {
      double b = pop_num_array(num_arr);
      double a = pop_num_array(num_arr);
      if (a == a && b == b) {
        res = use_operators(char_1, a, b, err);
        *err = !*err ? push_num_array(num_arr, res) : *err;
      } else {
        *err = 12;
      }
    } else if (priority == 8) {
      double a = pop_num_array(num_arr);
      if (a == a) {
        a *= -1;
        *err = push_num_array(num_arr, a);
      } else {
        *err = 12;
      }
    } else if (priority == 5) {
      double a = pop_num_array(num_arr);
      if (a == a) {
        res = use_functions(char_1, a, err);
        *err = !*err ? push_num_array(num_arr, res) : *err;
      } else {
        *err = 12;
      }
    }
  }
  if (src == ')' && !*err) {
    pop_operator_string(string_func);
  } else if (!*err) {
    push_operator_string(string_func, src);
  }
}

double use_functions(char ch, double a, int *err) {
  double result = 0.0;
  if (!*err) {
    if (ch == 's') {
      result = sin(a);
    } else if (ch == 'c') {
      result = cos(a);
    } else if (ch == 't') {
      result = tan(a);
    } else if (ch == 'a') {
      result = atan(a);
    } else if (ch == 'i') {
      if (a >= -1 && a <= 1) {
        result = asin(a);
      } else {
        *err = 7;
      }
    } else if (ch == 'o') {
      if (a >= -1.0 && a <= 1.0) {
        result = acos(a);
      } else {
        *err = 8;
      }
    } else if (ch == 'q') {
      if (a >= 0.0) {
        result = sqrt(a);
      } else {
        *err = 9;
      }
    } else if (ch == 'g') {
      if (a > 0.0) {
        result = log10(a);
      } else {
        *err = 10;
      }
    } else if (ch == 'l') {
      if (a > 0.0) {
        result = log(a);
      } else {
        *err = 11;
      }
    }
  }
  return result;
}

double use_operators(char cr, double a, double b, int *err) {
  double result = 0.0;
  if (!*err) {
    if (cr == '-') {
      result = a - b;
    } else if (cr == '+') {
      result = a + b;
    } else if (cr == '*') {
      result = a * b;
    } else if (cr == '/') {
      if (fabs(b) > 0.0) {
        result = a / b;
      } else {
        *err = 5;
      }
    } else if (cr == 'm') {
      if (fabs(b) > 0.0) {
        result = fmod(a, b);
      } else {
        *err = 6;
      }
    } else if (cr == '^') {
      result = pow(a, b);
    }
  }
  return result;
}

int string_to_num(char *string_dst, int *i, double *res) {
  int count_num = 0, count_dot = 0, err = 0, string_length = strlen(string_dst);
  char buff_num[255] = {0};
  while (((string_dst[*i] >= '0' && string_dst[*i] <= '9') ||
          string_dst[*i] == '.') &&
         !err && *i < string_length) {
    if (string_dst[*i] == '.') {
      count_dot++;
    }
    err = count_dot > 1 ? 1 : 0;
    buff_num[count_num] = string_dst[*i];
    count_num++;
    *i += 1;
  }
  buff_num[count_num] = '\0';
  *res = strtod(buff_num, NULL);
  return err;
}

void check_unar(char *input_string, char *new_string) {
  int i = 0, n = 0, string_length = strlen(input_string);
  for (; i < string_length;) {
    if (input_string[i] == '-' || input_string[i] == '+') {
      if (strchr("(/^m*", input_string[i - 1])) {
        new_string[n] = input_string[i] == '-' ? 'u' : 'p';
        i++;
        n++;
      } else {
        new_string[n++] = input_string[i++];
      }
    } else {
      new_string[n++] = input_string[i++];
    }
  }
}
