#include "calc.h"

double pop_num_array(num_array *dst) {
  double res = 0.0;
  if (dst->top_num >= 0) {
    res = dst->m_num[dst->top_num];
    dst->m_num[dst->top_num] = 0.0;
    dst->top_num -= 1;
  } else {
    res = NAN;
  }
  return res;
}

char pop_operator_string(operator_string *dst) {
  char res = 0;
  if (dst->top_operatoration >= 0) {
    res = dst->m_operatoration[dst->top_operatoration];
    dst->m_operatoration[dst->top_operatoration] = 0;
    dst->top_operatoration -= 1;
    dst->priority = get_prior(get_operator_string(*dst));
  } else {
    res = 127;
  }
  return res;
}

char get_operator_string(operator_string src) {
  char res = 0;
  if (src.top_operatoration >= 0) {
    res = src.m_operatoration[src.top_operatoration];
  } else {
    res = 127;
  }
  return res;
}

int push_num_array(num_array *dst, double src) {
  int res = 0;
  if (dst->top_num < 255) {
    dst->top_num += 1;
    dst->m_num[dst->top_num] = src;
  } else {
    res = 3;
  }
  return res;
}

int push_operator_string(operator_string *dst, char src) {
  int res = 0;
  if (dst->top_operatoration < 255) {
    dst->top_operatoration += 1;
    dst->m_operatoration[dst->top_operatoration] = src;
    dst->priority = get_prior(src);
  } else {
    res = 1;
  }
  return res;
}

int get_prior(char src) {
  int res = -20;
  if (src == '-' || src == '+') {
    res = 1;
  } else if (src == '*' || src == '/' || src == 'm') {
    res = 2;
  } else if (src == '^') {
    res = 6;
  } else if (src == '(' || src == ')') {
    res = 0;
  } else if (src == 'u') {
    res = 8;
  } else if (src == 's' || src == 'c' || src == 't' || src == 'a' ||
             src == 'q' || src == 'l' || src == 'i' || src == 'o' ||
             src == 'g') {
    res = 5;
  }
  return res;
}
