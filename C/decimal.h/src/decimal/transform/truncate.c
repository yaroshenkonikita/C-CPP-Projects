#include "../secondary/secondary_f.h"

int truncate_h(decimal value, decimal *result) {
  int res = 1;
  if (result) {
    int sign = get_sign(value);
    while (minusScale_trancate(&value)) {
    }
    decimal_cpy(value, result);
    set_sign(result, sign);
    res = 0;
  }
  return res;
}
