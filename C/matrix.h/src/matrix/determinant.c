#include "secondary.h"

int determinant(matrix_t *A, double *result) {
  int res = matrix_correct(A);
  if (res || !result) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    res = WRONG_MATRIX;
  } else {
    matrix_t det = {0};
    res = create_matrix(A->rows, A->columns, &det);
    if (!res) {
      // int flag = 0;
      // cpy_matrix(A, &det);
      // *result = gauss_determinant(&det /*, flag*/);
      // while (*result != *result && flag < A->rows) {
      //   flag++;
      //   cpy_matrix(A, &det);
      //   *result = gauss_determinant(&det, flag);
      // }
      // if (*result != *result) {
      //   cpy_matrix(A, &det);
      //   *result = matrixDet(&det);
      // }determinant_rek
      cpy_matrix(A, &det);
      *result = determinant_rek(&det);
      remove_matrix(&det);
    }
  }
  return res;
}
