#include "../secondary/secondary_f.h"

// копирует мантису до exp > -1, а потом пытается получить дробь
int from_float_to_decimal(float src, decimal *dst) {
  int res = 1;
  if (dst && src == src && src != INFINITY && src != -INFINITY &&
      src < DECIMAL_OVER_MAX && src > -DECIMAL_OVER_MAX) {
    decimal_zero(dst);
    unsigned int num = *((unsigned int *)&src);
    int exp = ((num >> 23) & 0xff) - 127;
    if (exp <= 95 && exp >= -93) {
      int index = 0, zero = 0, digit = 0;
      if (exp > -1) {
        setBit(dst, exp--, 1);
        for (index = 22; index != -1 && exp > -1;) {
          if ((num >> index) & 1) {
            setBit(dst, exp, 1);
          }
          index--;
          exp--;
        }
      }
      if (src < 0) {
        src = -src;
      }
      if (index != -1) {
        double number = src;
        for (int counter = 0; counter < 8; counter++) {
          number *= 10;
          number = fmod(number, 10);
          digit = number;
          if (digit != 0) {
            while (zero > 0) {
              mul_on_ten(*dst, dst);
              zero--;
            }
            if (mul_on_ten(*dst, dst)) {
              decimal buff_dec = {0};
              from_int_to_decimal(digit, &buff_dec);
              add_without_check_scale(*dst, buff_dec, dst);
            } /* else {
               break;
             }*/
            // это исключение должно сработать если float хранит в себе 29.
            // значащих цифр и одновременно дробную, по идее такого нет
          } else {
            zero++;
          }
        }
      }
      set_sign(dst, (num >> 31) & 1);
      res = 0;
    }
  }
  return res;
}
