#include "secondary.h"

int eq_matrix(matrix_t *A, matrix_t *B) {
  int res = matrix_correct(A) || matrix_correct(B);
  if (!res && A->columns == B->columns && A->rows == B->rows) {
    res = SUCCESS;
    for (int i = 0; i < A->rows && res == SUCCESS; i++) {
      for (int j = 0; j < A->columns && res == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          res = FAILURE;
        }
      }
    }
  }
  return res;
}
