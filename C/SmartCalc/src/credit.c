#include "calc.h"

int credit_annuity(double sum_credit, double time_credit, double per,
                   double *month_pay, double *over_pay, double *all_pay) {
  int err = 0;
  double per_m = (per / 12.0) / 100;
  *month_pay = per_m * pow(1 + per_m, time_credit) /
               (pow(1 + per_m, time_credit) - 1) * sum_credit;
  *over_pay = *month_pay * time_credit - sum_credit;
  *all_pay = *over_pay + sum_credit;
  if (isnan(*month_pay) || isinf(*month_pay)) {
    err = 1;
  }
  return err;
}

int credit_dif(double sum_credit, double time_credit, double per,
               double *month_pay_first, double *month_pay_last,
               double *over_pay, double *all_pay) {
  int err = 0;
  per = per / 100, *all_pay = 0.0, *month_pay_last = 0.0;
  double delta_m = sum_credit / time_credit, buf_sum = sum_credit;
  for (int i = 0; i < time_credit; i++) {
    *month_pay_last = buf_sum * per * 30.4166666666667 / 365 + delta_m;
    buf_sum = buf_sum - delta_m;
    *all_pay = *all_pay + *month_pay_last;
    if (!i) {
      *month_pay_first = *month_pay_last;
    }
  }
  *over_pay = *all_pay - sum_credit;
  if (isnan(*month_pay_first) || isinf(*month_pay_first) || isnan(delta_m) ||
      isinf(delta_m)) {
    err = 1;
  }

  return err;
}
