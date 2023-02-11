#include <math.h>
#include <stdlib.h>

// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

#define WRONG_MATRIX 2
#define INCORRECT_MATRIX 1
#define NORMAL_MATRIX 0

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7
#define EPS_T 1e-6

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int mult_number(matrix_t *A, double number, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int transpose(matrix_t *A, matrix_t *result);
int determinant(matrix_t *A, double *result);
int calc_complements(matrix_t *A, matrix_t *result);
int inverse_matrix(matrix_t *A, matrix_t *result);
