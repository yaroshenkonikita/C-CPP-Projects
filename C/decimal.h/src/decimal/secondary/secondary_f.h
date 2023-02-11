#include "../../decimal.h"
#include <stdbool.h>

// возвращает значение бита по от индекса 0 до 127 за пределами 0
bool getBit(decimal dst, int index);
// возвращает успех записи бита / 1 = ok, 0 != ok
bool setBit(decimal *dst, int index, int value);
// возвращает успех зануления всей структуры decimal / 1 = ok, 0 != ok
bool decimal_zero(decimal *dst);
// возвращает успех копирования структуры / 1 = ok, 0 != ok
bool decimal_cpy(decimal value, decimal *dst);
// возвращает значение Scale от 0 до 28
int get_scale(decimal dst);
// возвращает успех занесения exp в Scale / 1 = ok, 0 != ok
bool set_scale(decimal *dst, char exp);
// возвращает значение знака / 1 - | 0 +
bool get_sign(decimal dst);
// возвращает успех занесения знака / 1 = ok, 0 != ok
bool set_sign(decimal *dst, bool sign);
// возвращает успех операции / 1 = ok, 0 = infinity
bool plusBit(decimal *dst, int index);
// возвращает успех операции / 1 = ok, 0 != ok
bool minusBit(decimal *dst, int index);
// возвращает index бита который равен 1 начиная с 95 индекса / -1 если нет
// такого
int find_first_high_bit(decimal value_1);
// возвращает index несовпадающего бита / -1 если нет такого
int find_not_equal_bit(decimal value_1, decimal value_2);
// возвращает успех и ставит большее число в value_1 игнорируя знак / 1 = ok, 0
// != ok
bool switch_to_high_without_sign(decimal *value_1, decimal *value_2);
// возвращает истину / 1 = is zero, 0 = have value
bool is_zero(decimal value);
// возвращает успех сдвига числа decimal на индекс / 1 = ok, 0 =
// переполнениев любую из сторон. index раз число умножится на 2, если index
// положителен. либо index раз число поделится на 2, если index отрицателен
bool shift(decimal *value, int index);
// 0 = infinity, 1 = ok.
// result меняется только в случае успеха
bool add_without_check_scale(decimal value_1, decimal value_2,
                             decimal *result);
// 0 значит правое число больше левого, 1 = ok.
// result меняется только в случае успеха
bool sub_without_check_scale(decimal value_1, decimal value_2,
                             decimal *result);
// возвращает успех умножения.
// 1 = поместилось в decimal.
// 0 = число больше decimal или infinity
bool mul_without_check_scale(decimal value_1, decimal value_2,
                             decimal *result);
// повышает scale на 1
bool mul_on_ten(decimal value, decimal *result);
// возращает успех и заносит в result количество вычитаний value_2 из value_1.
// 0 = value_2 is zero or error
bool div_without_dot(decimal value_1, decimal value_2,
                    decimal *result_div, decimal *result_mod);
// возвращает успех / 0 != ok | 1 = ok
bool minusScale_round(decimal *result);
bool minusScale_trancate(decimal *result);
// возвращает успех / 0 != ok | 1 = ok
bool equalScale(decimal value_1, decimal *result_1, decimal value_2,
               decimal *result_2);
// возвращает успех / 0 != ok | 1 = ok
bool normalization(decimal value_1, decimal value_2,
                  decimal *result_1, decimal *result_2);
bool minusScale_bank_round(decimal *result);
bool minusScale_bank_round_without_check(decimal *result);
// для проверки
// #include <stdio.h>
// void bin_print(decimal *dst);