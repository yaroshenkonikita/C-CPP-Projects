#include "secondary.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (result && rows > 0 && columns > 0) {
    result->matrix = (double **)calloc(rows, sizeof(*result->matrix));
    if (result->matrix) {
      int i = 0;
      while (i < rows) {
        result->matrix[i] =
            (double *)calloc(columns, sizeof(*result->matrix[i]));
        if (!result->matrix[i++]) {
          break;
        }
      }
      result->columns = columns;
      result->rows = i;
      if (i != rows || !result->matrix[i - 1]) {
        remove_matrix(result);
      } else {
        res = NORMAL_MATRIX;
      }
    }
  }
  return res;
}
