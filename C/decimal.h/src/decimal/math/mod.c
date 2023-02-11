#include "../secondary/secondary_f.h"

int mod_h(decimal value_1, decimal value_2, decimal *result) {
  int res = 0;
  decimal buff_res = {0};
  decimal_zero(&buff_res);
  if (is_zero(value_2)) {
    res = 3;
  } else if (normalization(value_1, value_2, &value_1, &value_2)) {
    if (!is_zero(value_2)) {
      div_without_dot(value_1, value_2, NULL, &buff_res);
      if (is_zero(buff_res)) {
        decimal_zero(&buff_res);
      } else {
        set_scale(&buff_res, get_scale(value_1));
        set_sign(&buff_res, get_sign(value_1));
      }
    }
    if (result && !res) {
      decimal_cpy(buff_res, result);
    }
  }
  return res;
}
