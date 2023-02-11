#include "../secondary/secondary_f.h"

int round_h(decimal value, decimal *result) {
  int res = 1;
  if (result) {
    int sign = get_sign(value);
    if (get_scale(value) > 0) {
      while (get_scale(value) > 1) {
        minusScale_trancate(&value);
      }
      minusScale_round(&value);
    }
    decimal_cpy(value, result);
    set_sign(result, sign);
    res = 0;
  }
  return res;
}
