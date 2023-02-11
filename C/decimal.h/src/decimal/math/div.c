#include "../secondary/secondary_f.h"

int div_h(decimal value_1, decimal value_2, decimal *result) {
  int res = 0;
  decimal buff_res = {0};
  decimal_zero(&buff_res);
  if (is_zero(value_2)) {
    res = 3;
  }
  int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
  if (normalization(value_1, value_2, &value_1, &value_2) && !res) {
    if (!is_zero(value_2)) {
      decimal_zero(&buff_res);
      decimal buffer = {0}, ten = {{10, 0, 0, 0}};
      int error_mul = 0;
      while (!error_mul) {
        div_without_dot(value_1, value_2, &buffer, &value_1);
        add_without_check_scale(buff_res, buffer, &buff_res);
        if (!mul_without_check_scale(value_1, ten, &value_1)) {
          minusScale_bank_round_without_check(&value_2);
        }
        if (is_zero(value_1) || is_zero(value_2)) {
          break;
        } else {
          if (get_scale(buff_res) == 28) {
            error_mul++;
          } else if (!mul_on_ten(buff_res, &buff_res)) {
            error_mul++;
          }
        }
      }
      if (error_mul) {
        int mod_h = buffer.bits[LOW] % 2;
        div_without_dot(value_1, value_2, &buffer, NULL);
        if (((buffer.bits[LOW] == 5) && mod_h) || (buffer.bits[LOW] > 5)) {
          plusBit(&buff_res, 0);
        }
      }
      set_sign(&buff_res, sign_1 ^ sign_2);
      if (result && !res) {
        decimal_cpy(buff_res, result);
      }
    } else {
      // это работает только в том случае если после нормализации съела
      // значение после точки
      if (get_sign(value_1) == sign_2) {
        res = 1;
      } else {
        res = 2;
      }
    }
  }
  return res;
}
