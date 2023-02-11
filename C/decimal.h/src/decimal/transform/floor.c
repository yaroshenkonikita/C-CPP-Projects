#include "../secondary/secondary_f.h"

int floor_h(decimal value, decimal *result) {
  int res = 1;
  if (result) {
    if (get_scale(value) > 0) {
      int mod_f = 0, sign = get_sign(value);
      decimal mod_h = {0}, ten = {{10, 0, 0, 0}};
      div_without_dot(value, ten, NULL, &mod_h);
      while (minusScale_trancate(&value)) {
        if (!mod_f && !is_zero(mod_h)) {
          mod_f = 1;
          div_without_dot(value, ten, NULL, &mod_h);
        }
      }
      if (sign && mod_f) {
        set_sign(&value, sign);
        plusBit(&value, 0);
      }
    }
    decimal_cpy(value, result);
    res = 0;
  }
  return res;
}
