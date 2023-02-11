#include "secondary_f.h"

// возвращает значение бита по от индекса 0 до 127 за пределами 0
bool getBit(decimal dst, int index) {
  bool res = 0;
  if (index > -1 && index < 128) {
    unsigned char index_curr = index % 32;
    unsigned char bit_curr = index / 32;
    res = (dst.bits[bit_curr] >> index_curr) & 1;
  }
  return res;
}

// возвращает успех записи бита / 1 = ok, 0 != ok
bool setBit(decimal *dst, int index, int value) {
  bool res = 0;
  if (dst && index > -1 && index < 128) {
    int bit = getBit(*dst, index);
    unsigned char index_curr = index % 32;
    unsigned char bit_curr = index / 32;
    if (bit ^ value) {
      dst->bits[bit_curr] ^= (1 << index_curr);
    }
    res = 1;
  }
  return res;
}

// возвращает успех зануления всей структуры decimal / 1 = ok, 0 != ok
bool decimal_zero(decimal *dst) {
  bool res = 0;
  if (dst) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    res = 1;
  }
  return res;
}

// возвращает успех копирования структуры / 1 = ok, 0 != ok
bool decimal_cpy(decimal value, decimal *dst) {
  bool res = 0;
  if (dst) {
    dst->bits[0] = value.bits[0];
    dst->bits[1] = value.bits[1];
    dst->bits[2] = value.bits[2];
    dst->bits[3] = value.bits[3];
    res = 1;
  }
  return res;
}

// возвращает значение Scale от 0 до 28
int get_scale(decimal dst) { return (dst.bits[SCALE] >> 16) & 0xff; }

// возвращает успех занесения exp в Scale / 1 = ok, 0 != ok
bool set_scale(decimal *dst, char exp) {
  bool res = 0;
  if (dst && exp < 29 && exp > -1) {
    dst->bits[SCALE] &= INT_32U;
    dst->bits[SCALE] |= (exp << 16);
    res = 1;
  }
  return res;
}
// // для проверки
// // вывод decimal по битам
// // только на стадии разработки
// void bin_print(decimal *dst) {
//   printf("| ");
//   printf("%u", (dst->bits[3] >> 31) & 1);
//   printf(" | ");
//   for (int i = 30; i != 23; i--) printf("%u", (dst->bits[3] >> i) & 1);
//   printf(" | ");
//   for (int i = 23; i != 15; i--) printf("%u", (dst->bits[3] >> i) & 1);
//   printf(" | ");
//   printf("%d", get_scale(*dst));
//   printf(" | ");
//   for (int i = 15; i != -1; i--) printf("%u", (dst->bits[3] >> i) & 1);
//   printf(" |------| ");
//   for (int i = 0; i < 96; i++) {
//     printf("%u", getBit(*dst, i));
//     if (i == 31 || i == 63) {
//       printf(" | ");
//     } else if ((i + 1) % 8 == 0) {
//       printf(" ");
//     }
//   }
//   printf("\n\n");
// }

// возвращает значение знака / 1 - | 0 +
bool get_sign(decimal dst) { return (dst.bits[SCALE] >> 31) & 1; }

// возвращает успех занесения знака / 1 = ok, 0 != ok
bool set_sign(decimal *dst, bool sign) {
  bool res = 0;
  if (dst) {
    dst->bits[SCALE] &= ~INT_32U;
    dst->bits[SCALE] |= (sign << 31);
    res = 1;
  }
  return res;
}

// возвращает успех операции / 1 = ok, 0 = infinity
bool plusBit(decimal *dst, int index) {
  bool res = 0;
  if (index > -1 && index < 96) {
    res = 1;
    unsigned char index_curr = index % 32;
    unsigned char bit_curr = index / 32;
    if ((dst->bits[bit_curr] >> index_curr) & 1) {
      if (!plusBit(dst, index + 1)) {
        res = 0;
      }
    }
    if (res) {
      dst->bits[bit_curr] ^= (1 << index_curr);
    }
  }
  return res;
}

// возвращает успех операции / 1 = ok, 0 != ok
bool minusBit(decimal *dst, int index) {
  bool res = 0;
  if (dst && index > -1 && index < 96) {
    res = 1;
    unsigned char index_curr = index % 32;
    unsigned char bit_curr = index / 32;
    if (!((dst->bits[bit_curr] >> index_curr) & 1)) {
      if (!minusBit(dst, index + 1)) {
        res = 0;
      }
    }
    if (res) {
      dst->bits[bit_curr] ^= (1 << index_curr);
    }
  }
  return res;
}

// возвращает index бита который равен 1 начиная с 95 индекса / -1 если нет
// такого
int find_first_high_bit(decimal value_1) {
  int index = 95;
  if (get_scale(value_1) == 0) {
    while (getBit(value_1, index) == 0 && index != -1) {
      index--;
    }
  }
  return index;
}

// возвращает index несовпадающего бита / -1 если нет такого
int find_not_equal_bit(decimal value_1, decimal value_2) {
  int index = 95;
  if (get_scale(value_1) == get_scale(value_2)) {
    while (getBit(value_1, index) == getBit(value_2, index) && index != -1) {
      index--;
    }
  }
  return index;
}

// возвращает успех и ставит большее число в value_1 игнорируя знак.
// 1 = ok, 0 != ok
bool switch_to_high_without_sign(decimal *value_1, decimal *value_2) {
  bool res = 0;
  if (value_1 && value_2) {
    int index = 0;
    if ((index = find_not_equal_bit(*value_1, *value_2)) != -1) {
      if (getBit(*value_2, index) & 1) {
        decimal buff = {0};
        decimal_cpy(*value_1, &buff);
        decimal_cpy(*value_2, value_1);
        decimal_cpy(buff, value_2);
      }
    }
    res = 1;
  }
  return res;
}

// возвращает истину / 1 = is zero, 0 = have value
bool is_zero(decimal value) {
  bool res = 0;
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) {
    res = 1;
  }
  return res;
}

// возвращает успех сдвига числа decimal на индекс / 1 = ok, 0 =
// переполнение любую из сторон. index раз число умножится на 2, если index
// положителен. либо index раз число поделится на 2, если index отрицателен
bool shift(decimal *value, int index) {
  bool res = 0;
  if (value && index != 0) {
    int bit_num;
    int index_curr;
    if (index > 0) {
      index_curr = 95;
      bit_num = index_curr - index;
      while (index_curr != bit_num) {
        if (getBit(*value, index_curr)) {
          return 0;
        }
        index_curr--;
      }
      index_curr = 95;
      while (bit_num != -1) {
        setBit(value, index_curr, getBit(*value, bit_num));
        index_curr--;
        bit_num--;
      }
      while (index_curr != -1) {
        setBit(value, index_curr, 0);
        index_curr--;
      }
      res = 1;
    } else {
      index_curr = 0;
      bit_num = index_curr - index;
      while (index_curr != bit_num) {
        if (getBit(*value, index_curr)) {
          return 0;
        }
        index_curr++;
      }
      index_curr = 0;
      while (bit_num != 96) {
        setBit(value, index_curr, getBit(*value, bit_num));
        index_curr++;
        bit_num++;
      }
      while (index_curr != 96) {
        setBit(value, index_curr, 0);
        index_curr++;
      }
      res = 1;
    }
  } else if (index == 0) {
    res = 1;
  }
  return res;
}

// 0 = infinity, 1 = ok.
// result меняется только в случае успеха
bool add_without_check_scale(decimal value_1, decimal value_2,
                             decimal *result) {
  bool res = 0;
  if (result) {
    res = 1;
    for (int i = 0; i < 96; i++) {
      if (getBit(value_2, i)) {
        if (!plusBit(&value_1, i)) {
          res = 0;
          break;
        }
      }
    }
    if (res) {
      decimal_cpy(value_1, result);
    }
  }
  return res;
}

// 0 значит правое число больше левого, 1 = ok.
// result меняется только в случае успеха
bool sub_without_check_scale(decimal value_1, decimal value_2,
                             decimal *result) {
  bool res = 0;
  if (result) {
    res = 1;
    for (int i = 95; i > -1; i--) {
      if (getBit(value_2, i)) {
        if (!minusBit(&value_1, i)) {
          res = 0;
          break;
        }
      }
    }
    if (res) {
      decimal_cpy(value_1, result);
    }
  }
  return res;
}

// возвращает успех умножения.
// 1 = поместилось в decimal.
// 0 = число больше decimal или infinity
bool mul_without_check_scale(decimal value_1, decimal value_2,
                             decimal *result) {
  bool res = 0;
  decimal buffer = {0};
  if (result) {
    int index = 0;
    res = 1;
    if (!(is_zero(value_1) || is_zero(value_2))) {
      for (int i = 0; i < 96; i++) {
        if (getBit(value_2, i)) {
          if (!shift(&value_1, i - index)) {
            res = 0;
          } else {
            index = i;
            if (!add_without_check_scale(buffer, value_1, &buffer)) {
              res = 0;
            }
          }
          if (!res) {
            break;
          }
        }
      }
      if (res && (get_sign(value_1) != get_sign(value_2))) {
        set_sign(&buffer, 1);
        decimal_cpy(buffer, result);
      } else if (res) {
        set_sign(&buffer, 0);
        decimal_cpy(buffer, result);
      }
    } else {
      decimal_zero(result);
      res = 1;
    }
  }
  return res;
}

// умножает на 10 и повышает scale на 1
bool mul_on_ten(decimal value, decimal *result) {
  bool res = 0;
  if (result) {
    decimal ten = {{10, 0, 0, 0}};
    int scale = get_scale(value);
    if (scale < 28 && mul_without_check_scale(value, ten, &value)) {
      set_scale(&value, scale + 1);
      res = 1;
      decimal_cpy(value, result);
    }
  }
  return res;
}

// возращает успех и заносит в result количество вычитаний value_2 из value_1.
// 0 = value_2 is zero or error
bool div_without_dot(decimal value_1, decimal value_2,
                     decimal *result_div, decimal *result_mod) {
  bool res = 0;
  int index = 0;
  if (result_div || result_mod) {
    if (!is_zero(value_2)) {
      res = 1;
      while (shift(&value_2, 1)) {
        index++;
      }
      decimal mod_h = {0}, buff_res = {0};
      while (index > -1 && res) {
        if (!sub_without_check_scale(value_1, value_2, &mod_h)) {
        } else {
          decimal_cpy(mod_h, &value_1);
          plusBit(&buff_res, index);
        }
        if (index-- > 0) {
          res = shift(&value_2, -1);
        } else {
          shift(&value_2, -1);
        }
      }
      if (res) {
        if (result_div) {
          decimal_cpy(buff_res, result_div);
        }
        if (result_mod) {
          decimal_cpy(value_1, result_mod);
        }
      }
    } /* else {
       res = 0;
     }*/
    // это исключение сработает только в том случае если подать 0 в value_2.
    // но я так не сделаю, а у вас не получится
  }
  return res;
}

// возвращает успех / 0 != ok | 1 = ok
bool minusScale_round(decimal *result) {
  bool res = 0;
  decimal mod_h = {0}, ten = {{10, 0, 0, 0}};
  int scale = get_scale(*result);
  if (get_scale(*result) > 0 && div_without_dot(*result, ten, NULL, &mod_h)) {
    if (div_without_dot(*result, ten, result, NULL)) {
      if (mod_h.bits[0] > 4) {
        plusBit(result, 0);
      }
      set_scale(result, scale - 1);
      res = 1;
    }
  }
  return res;
}

// возвращает успех / 0 != ok | 1 = ok
bool minusScale_trancate(decimal *result) {
  bool res = 0;
  decimal ten = {{10, 0, 0, 0}};
  int scale = get_scale(*result);
  int sign = get_sign(*result);
  if (scale > 0) {
    if (div_without_dot(*result, ten, result, NULL)) {
      set_scale(result, scale - 1);
      set_sign(result, sign);
      res = 1;
    }
  }
  return res;
}

bool minusScale_bank_round(decimal *result) {
  bool res = 0;
  if (result) {
    int scale = get_scale(*result);
    int sign = get_sign(*result);
    if (scale > 0) {
      decimal buffer = *result, ten = {{10, 0, 0, 0}};
      div_without_dot(buffer, ten, result, &buffer);
      int mod_h = buffer.bits[LOW];
      div_without_dot(*result, ten, NULL, &buffer);
      if (buffer.bits[LOW] >= 5) {
        if (buffer.bits[LOW] == 5 && mod_h % 2) {
          plusBit(result, 0);
        } else if (buffer.bits[LOW] > 5) {
          plusBit(result, 0);
        }
      }
      set_scale(result, scale - 1);
      set_sign(result, sign);
      res = 1;
    }
  }
  return res;
}

bool minusScale_bank_round_without_check(decimal *result) {
  bool res = 0;
  if (result) {
    decimal buffer = *result, ten = {{10, 0, 0, 0}};
    div_without_dot(buffer, ten, result, &buffer);
    int mod_h = buffer.bits[LOW] % 2;
    div_without_dot(*result, ten, NULL, &buffer);
    if ((buffer.bits[LOW] == 5 && mod_h) || buffer.bits[LOW] > 5) {
      plusBit(result, 0);
    }
    res = 1;
  }
  return res;
}

// возвращает успех / 0 != ok | 1 = ok
// идет в сторону одинаковых скейлов
bool equalScale(decimal value_1, decimal *result_1, decimal value_2,
                decimal *result_2) {
  bool res = 0;
  if (result_1 && result_2) {
    res = 1;
    if (!mul_on_ten(value_2, &value_2)) {
      res = minusScale_bank_round(&value_1);
    }
    if (res) {
      decimal_cpy(value_1, result_1);
      decimal_cpy(value_2, result_2);
    }
  }
  return res;
}

// возвращает успех / 0 != ok | 1 = ok.
// приравниваек к одному скейлу
bool normalization(decimal value_1, decimal value_2,
                   decimal *result_1, decimal *result_2) {
  bool res = 0;
  if (result_1 && result_2) {
    res = 1;
    int scale_1 = get_scale(value_1), scale_2 = get_scale(value_2);
    while (scale_1 != scale_2) {
      if (scale_1 > scale_2) {
        res = equalScale(value_1, &value_1, value_2, &value_2);
      } else {
        res = equalScale(value_2, &value_2, value_1, &value_1);
      }
      scale_1 = get_scale(value_1), scale_2 = get_scale(value_2);
    }
    if (res) {
      decimal_cpy(value_1, result_1);
      decimal_cpy(value_2, result_2);
    }
  }
  return res;
}
