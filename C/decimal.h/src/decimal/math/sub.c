#include "../secondary/secondary_f.h"

int sub_h(decimal value_1, decimal value_2, decimal *result) {
  int res = 0;
  decimal buff_res = {0};
  decimal_zero(&buff_res);
  if (normalization(value_1, value_2, &value_1, &value_2)) {
    // меняю местами если второй больше без знака, копирую больший в value_1
    if (switch_to_high_without_sign(&value_1, &value_2)) {
      if (get_sign(value_1) == get_sign(value_2)) {
        sub_without_check_scale(value_1, value_2, &buff_res);
      } else {
        while (!add_without_check_scale(value_1, value_2, &buff_res)) {
          if (get_scale(value_1) > 0 && get_scale(value_2) > 0) {
            minusScale_bank_round(&value_1);
            minusScale_bank_round(&value_2);
          } else {
            if (get_sign(value_1)) {
              res = 2;
            } else {
              res = 1;
            }
            break;
          }
        }
      }
      set_sign(&buff_res, get_sign(value_1));
      if (result && !res) {
        decimal_cpy(buff_res, result);
      }
    }
  }
  return res;
}
