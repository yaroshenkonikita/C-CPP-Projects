#include <math.h>
// #define NAN (0.0 / 0.0)
// #define INFINITY (1.0 / 0.0)
#define INT_32U 2147483648U
#define NULL ((void *)0)
#define DECIMAL_MAX_INDEX pow(2, 95)
#define DECIMAL_OVER_MAX pow(2, 96)

// struct decimal
typedef struct {
  unsigned int bits[4];
} decimal;

//                       0     1      2      3
enum decimal_enum { LOW, MIDDLE, HIGH, SCALE };

// result = value_1 + value_2.
// 0 = OK | 1 = inf | 2 = -inf | 3 = value_2 is zero
int add_h(decimal value_1, decimal value_2, decimal *result);
// result = value_1 * value_2.
// 0 = OK | 1 = inf | 2 = -inf | 3 = value_2 is zero
int mul_h(decimal value_1, decimal value_2, decimal *result);
// result = value_1 - value_2.
// 0 = OK | 1 = inf | 2 = -inf | 3 = value_2 is zero
int sub_h(decimal value_1, decimal value_2, decimal *result);
// result = value_1 % value_2.
// 0 = OK | 1 = inf | 2 = -inf | 3 = value_2 is zero
int mod_h(decimal value_1, decimal value_2, decimal *result);
// result = value_1 / value_2.
// 0 = OK | 1 = inf | 2 = -inf | 3 = value_2 is zero
int div_h(decimal value_1, decimal value_2, decimal *result);
// value_1 >= value_2.
// 1 = TRUE | 0 = FALSE
int is_greater_or_equal(decimal value_1, decimal value_2);
// value_1 <= value_2.
// 1 = TRUE | 0 = FALSE
int is_less_or_equal(decimal value_1, decimal value_2);
// value_1 > value_2.
// 1 = TRUE | 0 = FALSE
int is_greater(decimal value_1, decimal value_2);
// value_1 < value_2.
// 1 = TRUE | 0 = FALSE
int is_less(decimal value_1, decimal value_2);
// value_1 == value_2.
// 1 = TRUE | 0 = FALSE
int is_equal(decimal value_1, decimal value_2);
// value_1 != value_2.
// 1 = TRUE | 0 = FALSE
int is_not_equal(decimal value_1, decimal value_2);
// result = -value.
// 1 = have n't ptr | 0 = OK
int negate_h(decimal value, decimal *result);
// rounds down to minus infinity
// 1 = have n't ptr | 0 = OK
int floor_h(decimal value, decimal *result);
// rounds to the nearest whole number
// 1 = have n't ptr | 0 = OK
int round_h(decimal value, decimal *result);
// discards the fractional part
// 1 = have n't ptr | 0 = OK
int truncate_h(decimal value, decimal *result);
// 1 = have n't ptr | 0 = OK
// int(src) -> decimal(dst)
int from_int_to_decimal(int src, decimal *dst);
// 1 = have n't ptr | 0 = OK
// decimal(src) -> int(dst)
int from_decimal_to_int(decimal src, int *dst);
// 1 = have n't ptr | 0 = OK
// float(src) -> decimal(dst)
int from_float_to_decimal(float src, decimal *dst);
// 1 = have n't ptr | 0 = OK
// decimal(src) -> float(dst)
int from_decimal_to_float(decimal src, float *dst);