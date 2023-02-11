#include "secondary.h"

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = matrix_correct(A);
  if (res || !result) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    res = WRONG_MATRIX;
  } else {
    res = WRONG_MATRIX;
    double det = 0;
    determinant(A, &det);
    if (fabs(det) > 1e-6 && det == det) {
      det = 1 / det;
      matrix_t minor_buff = {0}, transpose_buff = {0};
      if (!calc_complements(A, &minor_buff)) {
        if (!transpose(&minor_buff, &transpose_buff)) {
          if (!mult_number(&transpose_buff, det, result)) {
            res = NORMAL_MATRIX;
          }
          remove_matrix(&transpose_buff);
        }
        remove_matrix(&minor_buff);
      }
    }
  }
  return res;
}
