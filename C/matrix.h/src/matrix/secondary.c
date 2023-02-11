#include "secondary.h"

void get_minor(matrix_t *A, matrix_t *minor, int skip_row, int skip_column) {
  int index_i = 0;
  for (int i = 0; i < A->rows; i++) {
    int index_j = 0;
    if (i != skip_row) {
      for (int j = 0; j < A->columns; j++) {
        if (j != skip_column) {
          *(*((minor->matrix) + index_i) + index_j) = *(*((A->matrix) + i) + j);
          index_j++;
        }
      }
      index_i++;
    }
  }
}

void cpy_matrix(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      *(*((result->matrix) + i) + j) = *(*((A->matrix) + i) + j);
    }
  }
  result->columns = A->columns;
  result->rows = A->rows;
}

int matrix_correct(matrix_t *matrix) {
  int res = INCORRECT_MATRIX;
  if (matrix && matrix->matrix && matrix->columns > 0 && matrix->rows > 0) {
    res = NORMAL_MATRIX;
    // for (int i = 0; i < matrix->rows && res == NORMAL_MATRIX; i++) {
    //   for (int j = 0; j < matrix->columns && res == NORMAL_MATRIX; j++) {
    //     if (matrix->matrix[i]) {
    //       if (!(matrix->matrix[i] + j)) {
    //         res = WRONG_MATRIX;
    //       }
    //     } else {
    //       res = WRONG_MATRIX;
    //     }
    //   }
    // }
  }
  return res;
}

// рабочий в большенстве случаев, не работает в случаях если.
// при затерании нижнего треугольника затрется диагональ
// double gauss_determinant(matrix_t *A /*, int flag*/) {
//   double res = 1;
//   int i_index_buff = 1;
//   /* for (int index = 0;
//        index < A->columns && A->columns > 2 && flag <= A->columns && flag;
//        index++) {
//     if (flag < A->columns) {
//       A->matrix[flag - 1][index] += A->matrix[flag][index];
//     } else {
//       A->matrix[flag - 1][index] += A->matrix[0][index];
//     }
//   } */
//   for (int j = 0; j < A->columns - 1; j++, i_index_buff++) {
//     double value_center = A->matrix[j][j];
//     for (int i = i_index_buff; i < A->columns; i++) {
//       if (A->matrix[i][j] != 0) {
//         double buff = A->matrix[i][j] / value_center;
//         int j_index_buff = j;
//         while (j_index_buff < A->columns) {
//           A->matrix[i][j_index_buff] =
//               A->matrix[i][j_index_buff] - (A->matrix[j][j_index_buff] *
//               buff);
//           j_index_buff++;
//         }
//       }
//     }
//   }
//   for (int i = 0; i < A->columns; i++) {
//     res *= A->matrix[i][i];
//   }
//   return (double)res;
// }

double determinant_rek(matrix_t *A) {
  double det = 0;
  double minus = 1;
  if (A->columns == 1) {
    det = A->matrix[0][0];
  } else if (A->columns == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    matrix_t buff = {0};
    create_matrix(A->rows - 1, A->columns - 1, &buff);
    for (int j = 0; j < A->rows; j++) {
      get_minor(A, &buff, 0, j);
      det = det + (minus * A->matrix[0][j] * determinant_rek(&buff));
      minus = -minus;
    }
    remove_matrix(&buff);
  }
  return det;
}

void algeb_dop(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] *= pow(-1.0, (double)(i + j));
    }
  }
}