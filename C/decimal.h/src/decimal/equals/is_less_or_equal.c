#include "../secondary/secondary_f.h"

int is_less_or_equal(decimal value_1, decimal value_2) {
  return !is_greater(value_1, value_2);
}
