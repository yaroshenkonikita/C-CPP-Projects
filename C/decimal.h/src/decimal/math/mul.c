#include "../secondary/secondary_f.h"

int mul_h(decimal value_1, decimal value_2, decimal *result) {
  int res = 0;
  decimal buffer = {0};
  while (!mul_without_check_scale(value_1, value_2, &buffer)) {
    int scale_1 = get_scale(value_1), scale_2 = get_scale(value_2);
    if (scale_1 > 0 || scale_2 > 0) {
      if (scale_1 == scale_2) {
        minusScale_bank_round(&value_1);
        minusScale_bank_round(&value_2);
      } else if (scale_1 > scale_2) {
        minusScale_bank_round(&value_1);
      } else {
        minusScale_bank_round(&value_2);
      }
    } else {
      if (get_sign(value_1) == get_sign(value_2)) {
        res = 1;
      } else {
        res = 2;
      }
      break;
    }
  }
  if (result && !res) {
    decimal_cpy(buffer, result);
    set_scale(result, get_scale(value_1) + get_scale(value_2));
    set_sign(result, get_sign(value_1) ^ get_sign(value_2));
  }
  return res;
}
