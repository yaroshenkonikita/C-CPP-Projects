#include "../secondary/secondary_f.h"

int negate_h(decimal value, decimal *result) {
  int res = 1;
  if (decimal_cpy(value, result)) {
    result->bits[SCALE] ^= INT_32U;
    res = 0;
  }
  return res;
}
