#include "secondary.h"

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = matrix_correct(A) || matrix_correct(B);
  if (res || !result) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    res = WRONG_MATRIX;
  } else {
    res = create_matrix(A->rows, A->columns, result);
    if (!res) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return res;
}
