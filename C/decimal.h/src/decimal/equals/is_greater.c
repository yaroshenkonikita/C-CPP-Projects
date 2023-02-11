#include "../secondary/secondary_f.h"

int is_greater(decimal value_1, decimal value_2) {
  int res = 0;
  normalization(value_1, value_2, &value_1, &value_2);
  res = find_not_equal_bit(value_1, value_2);
  int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
  if (res > -1) {
    int bit = getBit(value_1, res);
    if (bit) {
      res = 1;
    } else {
      res = 0;
    }
    if (sign_1 && sign_2) {
      res ^= 1;
    } else if (sign_1) {
      res = 0;
    } else if (sign_2) {
      res = 1;
    }
  } else {
    res = 0;
    if (sign_2 && !sign_1) {
      res = 1;
    }
  }
  return res;
}
