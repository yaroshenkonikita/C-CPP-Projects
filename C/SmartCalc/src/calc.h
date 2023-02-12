#include <math.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Stack array double
 *
 * @param m_num - stack array
 * @param top_num - where is last element in stack
 */
typedef struct stack_num {
  double m_num[255];
  int top_num;
} num_array;

/**
 * @brief Stack array chars(operators)
 *
 * @param m_operatoration - stack array
 * @param top_operatoration - where is last element in stack
 * @param priority - priority last operation in stack
 */
typedef struct stack_op {
  char m_operatoration[255];
  int top_operatoration;
  int priority;
} operator_string;

/*!
 * @brief Copy from `input_string` with no conflict double operations,
 *        for example 1*-1 he rework in 1*u1, where `u` is unar minus.
 *
 * @param input_string - src string
 * @param new_string - new string
 */
void check_unar(char *input_string, char *new_string);

//  stack
/**
 * @brief Get last element from stack with remove.
 *
 * @param dst - struct number
 * @return double number, if empty - NAN
 */
double pop_num_array(num_array *dst);
/**
 * @brief Get last element from stack with remove.
 *
 * @param dst - struct operation
 * @return char operation, if empty - value 127
 */
char pop_operator_string(operator_string *dst);
/**
 * @brief Add element number in last position.
 *
 * @param dst - struct operation
 * @param src - number
 * @return int 0 if okey, 3 if stack is over
 */
int push_num_array(num_array *dst, double src);
/**
 * @brief Add char operator in last position.
 *
 * @param dst - struct operation
 * @param src - char operator
 * @return int 0 if okey, 3 if stack is over
 */
int push_operator_string(operator_string *dst, char src);
/**
 * @brief Get last element from stack without remove.
 *
 * @param dst - struct number
 * @return double number, if empty - NAN
 */
double get_num_array(num_array dst);
/**
 * @brief Get last element from stack without remove.
 *
 * @param dst - struct operation
 * @return char operation, if empty - value 127
 */
char get_operator_string(operator_string src);
/**
 * @brief Get priority char operation.
 *
 * @param src - char operator
 * @return int priority 1 if "-+", 2 if "/m*", 6 if '^',
 *         8 if 'u', 5 if math function, 0 if bracket.
 */
int get_prior(char src);

//  math and calc
/**
 * @brief Logic function.
 *
 * @param new_string - string calc
 * @param out - answer
 * @param x - x value
 * @return int 0 ok, other err.
 */
int calc_work(char *new_string, double *out, double x);
/**
 * @brief Itoi.
 *
 * @param string_dst - string with start digit
 * @param i - iterator
 * @param res - num
 * @return int 0 ok, other err.
 */
int string_to_num(char *string_dst, int *i, double *res);
/**
 * @brief Use math operators.
 *
 * @param cr - char - func
 * @param a - first number
 * @param b - second number
 * @param err - error return
 * @return double answer number.
 */
double use_operators(char cr, double a, double b, int *err);
/**
 * @brief Use math function.
 *
 * @param cr - char - func
 * @param a - number
 * @param err - error return
 * @return double answer number.
 */
double use_functions(char ch, double a, int *err);
/**
 * @brief Logic data in stacks.
 *
 * @param string_func - stack chars
 * @param num_arr - stack numbers
 * @param err - error return
 * @param src - find what need to take with them
 */
void stack_processing(operator_string *string_func, num_array *num_arr,
                      int *err, char src);
/**
 * @brief Function to start answer on string quest.
 *
 * @param input_string - string quest
 * @param out - answer number
 * @param x - x value
 * @return int 0 is okey, other is err.
 */
int s21_calc(char *input_string, double *out, double x);

//  deposit calc
/**
 * @brief Get sum from list to month.
 *
 * @param re1 - array of number month
 * @param re2 - array of money in this month
 * @param count_re - all month
 * @param count_month - needs month
 * @return double sum money.
 */
double get_re_list(double *re1, double const *re2, int count_re,
                   int count_month);
/**
 * @brief Get sum from list to month, but no high of all money.
 *
 * @param wi1 - array of number month
 * @param wi2 - array of money in this month
 * @param count_wi - all month
 * @param count_month - needs month
 * @param all_sum - all money in bank
 * @return double sum money, is over - 0.0.
 */
double get_wi_list(double *wi1, double const *wi2, int count_wi,
                   int count_month, double all_sum);
/**
 * @brief Deposit calc.
 *
 * @param re1 - array of number month
 * @param re2 - array of money in this month
 * @param count_re - all month
 * @param wi1 - array of number month
 * @param wi2 - array of money in this month
 * @param count_wi - all month
 * @param all_sum - all money in bank
 * @param tern - deposit term
 * @param interest - interest rate
 * @param tax - tax
 * @param period_s - payment period
 * @param kap - interest capitalization
 * @param all_interest - return total interest
 * @param all_tax - return tax
 * @param all_sum_after - return total sum
 * @return int 0 is okey, other is err.
 */
int deposit_calculator(double *re1, double *re2, int count_re, double *wi1,
                       double *wi2, int count_wi, double all_sum, double tern,
                       double interest, double tax, int period_s, int kap,
                       double *all_interest, double *all_tax,
                       double *all_sum_after);

//  credit calc
/**
 * @brief Credit annuity calc.
 *
 * @param sum_credit - sum of credit
 * @param time_credit - credit term
 * @param per - interest rate
 * @param month_pay - return monthly payment
 * @param over_pay - return overpayment on a loan
 * @param all_pay - return final payment on the loan
 * @return int 0 is okey, other is err.
 */
int credit_annuity(
    double sum_credit, double time_credit, double per, double *month_pay,
    double *over_pay,
    double *all_pay); /**
                       * @brief Credit differential calc.
                       *
                       * @param sum_credit - sum of credit
                       * @param time_credit - credit term
                       * @param per - interest rate
                       * @param month_pay_first - return first monthly payment
                       * @param month_pay_last - return last monthly payment
                       * @param over_pay - return overpayment on a loan
                       * @param all_pay - return final payment on the loan
                       * @return int 0 is okey, other is err.
                       */
int credit_dif(double sum_credit, double time_credit, double per,
               double *month_pay_first, double *month_pay_last,
               double *over_pay, double *all_pay);
