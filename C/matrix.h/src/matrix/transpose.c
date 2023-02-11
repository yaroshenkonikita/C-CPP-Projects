#include "secondary.h"

int transpose(matrix_t *A, matrix_t *result) {
  int res = matrix_correct(A);
  if (res || !result) {
    res = INCORRECT_MATRIX;
  } else {
    res = create_matrix(A->columns, A->rows, result);
    if (!res) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return res;
}
