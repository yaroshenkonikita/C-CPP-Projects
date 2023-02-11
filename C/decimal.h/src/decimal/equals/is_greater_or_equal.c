#include "../secondary/secondary_f.h"

int is_greater_or_equal(decimal value_1, decimal value_2) {
  return !is_less(value_1, value_2);
}
