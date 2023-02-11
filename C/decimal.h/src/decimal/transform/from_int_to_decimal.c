#include "../secondary/secondary_f.h"

int from_int_to_decimal(int src, decimal *dst) {
  int result = 1;
  if (dst) {
    decimal_zero(dst);
    if (src < 0) {
      src = -src;
      dst->bits[SCALE] = INT_32U;
      // src ^= INT_32U;
    }
    dst->bits[LOW] = src;
    if (dst->bits[LOW] == (unsigned int)src) {
      result = 0;
    }
  }
  return result;
}
