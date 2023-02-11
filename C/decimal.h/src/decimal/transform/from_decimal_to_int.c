#include "../secondary/secondary_f.h"

int from_decimal_to_int(decimal src, int *dst) {
  int res = 1;
  if (dst) {
    while (minusScale_trancate(&src)) {
    }
    int index = find_first_high_bit(src);
    if (index < 31 && res) {
      *dst = src.bits[LOW];
      if (get_sign(src)) {
        *dst *= -1;
      }
      res = 0;
    }
    if (get_sign(src) && src.bits[0] == 2147483648 && index < 32) {
      *dst = 0b10000000000000000000000000000000;
      res = 0;
    }
  }
  return res;
}
