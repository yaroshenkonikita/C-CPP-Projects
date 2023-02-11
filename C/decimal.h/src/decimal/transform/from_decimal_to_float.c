#include "../secondary/secondary_f.h"

int from_decimal_to_float(decimal src, float *dst) {
  int res = 1;
  if (dst) {
    *dst = 0;
    double asd = 0;
    for (int i = 95; i != -1; i--) {
      if (getBit(src, i)) {
        asd += pow(2.0, i);
      }
    }
    asd /= (pow(10, get_scale(src)));
    if (get_sign(src)) {
      asd = -asd;
    }
    *dst = asd;
    res = 0;
  }
  return res;
}
