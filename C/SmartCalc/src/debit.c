#include "calc.h"

double get_re_list(double *re1, double const *re2, int count_re,
                   int count_month) {
  double buf = 0.0;
  for (int i = 0; i < count_re; i++) {
    int z = (int)re1[i];
    if (z == count_month) {
      buf += re2[i];
    }
  }
  return buf;
}

double get_wi_list(double *wi1, double const *wi2, int count_wi,
                   int count_month, double all_sum) {
  double buf = 0.0;
  for (int i = 0; i < count_wi; i++) {
    int z = (int)wi1[i];
    if (z == count_month) {
      buf += wi2[i];
    }
  }
  if (buf > all_sum)
    buf = all_sum;
  return buf;
}

int deposit_calculator(double *re1, double *re2, int count_re, double *wi1,
                       double *wi2, int count_wi, double all_sum, double tern,
                       double interest, double tax, int period_s, int kap,
                       double *all_interest, double *all_tax,
                       double *all_sum_after) {
  int err = 0;
  *all_interest = 0.0;
  *all_sum_after = 0.0;
  *all_tax = 0.0;
  interest = interest / 100;
  tax = tax / 100;
  if (kap == 0) {
    for (int i = 1; i <= tern; i++) {
      all_sum += get_re_list(re1, re2, count_re, i);
      all_sum -= get_wi_list(wi1, wi2, count_wi, i, all_sum);
      *all_interest += interest / 12 * all_sum;
    }
    *all_sum_after = all_sum;
  } else {
    int p = 0;
    for (int i = 1; i <= tern; i++) {
      all_sum += get_re_list(re1, re2, count_re, i);
      all_sum -= get_wi_list(wi1, wi2, count_wi, i, all_sum);
      if (i % period_s == 0) {
        *all_interest +=
            (interest / 12.0) * period_s * (all_sum + *all_interest);
        p = i;
      } else if (i == tern) {
        int z = i - p;
        *all_interest += (interest / 12.0) * z * (all_sum + *all_interest);
      }
    }
    *all_sum_after = *all_interest + all_sum;
  }
  *all_tax = ((*all_interest / tern) - (95000 / 12.0)) * tern * tax;

  *all_tax = *all_tax < 0 ? 0.0 : *all_tax;
  if (isnan(*all_interest) != 0 || isinf(*all_interest) != 0 ||
      isnan(*all_sum_after) != 0 || isinf(*all_sum_after) != 0 ||
      isnan(*all_tax) != 0 || isinf(*all_tax) != 0) {
    err = 1;
  }
  return err;
}
