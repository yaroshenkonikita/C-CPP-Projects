#include "secondary.h"

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = matrix_correct(A) || matrix_correct(B);
  if (res || !result) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    res = WRONG_MATRIX;
  } else {
    res = create_matrix(A->rows, B->columns, result);
    if (!res) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          double buffer = 0;
          for (int index = 0; index < A->columns; index++) {
            buffer += A->matrix[i][index] * B->matrix[index][j];
          }
          result->matrix[i][j] = buffer;
        }
      }
    }
  }
  return res;
}
