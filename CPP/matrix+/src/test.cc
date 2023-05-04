#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(Basic, default_constructor) {
  s21::Matrix<double> basic;
  EXPECT_EQ(basic.GetRows(), 3);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(Basic, default_constructor_Exception) {
  EXPECT_ANY_THROW(s21::Matrix<double> exception(1, 0));
}

TEST(Basic, parameterized_constructor) {
  s21::Matrix<double> basic(2, 3);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(Basic, parameterized_constructor_Exception) {
  EXPECT_ANY_THROW(s21::Matrix<double> exception(0, -2));
}

TEST(Basic, copy_constructor) {
  s21::Matrix<double> basic(2, 3);
  s21::Matrix<double> result(basic);
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetColumns(), 3);
  EXPECT_EQ(basic == result, true);
}

TEST(Basic, move_constructor) {
  s21::Matrix<double> basic(2, 3);
  s21::Matrix<double> result(std::move(basic));
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetColumns(), 3);
  EXPECT_EQ(basic.GetRows(), 3);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(GetterAndSetter, set) {
  s21::Matrix<double> basic(2, 3);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetColumns(), 3);
  basic.Set(4, 3);
  basic(3, 2) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(3, 2), 1.2);
  EXPECT_EQ(basic.GetRows(), 4);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(assignmentOperator, brakets) {
  s21::Matrix<double> basic(2, 3);
  basic(1, 1) = 3;
  EXPECT_EQ(basic(1, 1), 3);
}

TEST(assignmentOperator, brakets_Exception) {
  s21::Matrix<double> exception(2, 3);
  EXPECT_ANY_THROW(exception(1, 5));
}

TEST(functionalFuncTest, braket_Exception2) {
  s21::Matrix<double> exception(1, 1);
  EXPECT_ANY_THROW(exception(5, 0) = 5);
}

TEST(supportFunction, set_zero_Matrix) {
  s21::Matrix<double> basic;
  EXPECT_EQ(basic.GetRows(), 3);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(assignmentOperator, moveConst) {
  s21::Matrix<double> basic(2, 3);
  s21::Matrix<double> basic2 = std::move(basic);
  EXPECT_EQ(basic.GetRows(), 3);
  EXPECT_EQ(basic.GetColumns(), 3);
  EXPECT_EQ(basic2.GetRows(), 2);
  EXPECT_EQ(basic2.GetColumns(), 3);
}

TEST(functionalTest, copy) {
  s21::Matrix<double> a(2, 2);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a = b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, plus) {
  s21::Matrix<double> a(2, 2);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  s21::Matrix<double> result = a + b;
  EXPECT_DOUBLE_EQ(result(1, 1), 3.3);
}

TEST(functionalTest, plus2) {
  s21::Matrix<double> a(2, 2);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(functionalTest, plus3) {
  s21::Matrix<double> a(2, 2);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(functionalTest, plus_Exception) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(s21::Matrix<double> result = a + b);
}

TEST(functionalTest, plus_Exception2) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(functionalTest, plus_Exception3) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(functionalTest, minus) {
  s21::Matrix<double> a(2, 2);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  s21::Matrix<double> result = a - b;
  EXPECT_DOUBLE_EQ(result(1, 1), -1.1);
}

TEST(functionalTest, minus2) {
  s21::Matrix<double> a(2, 2);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, minus3) {
  s21::Matrix<double> a(2, 2);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, minus_Exception) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(s21::Matrix<double> result = a + b);
}

TEST(functionalTest, minus_Exception2) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(functionalTest, minus_Exception3) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(functionalTest, minus_Exception4) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a - b);
}

TEST(functionalTest, mult_Matrix) {
  s21::Matrix<double> a(3, 2);
  s21::Matrix<double> b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  s21::Matrix<double> result = a * b;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(functionalTest, mult_Matrix2) {
  s21::Matrix<double> a(3, 2);
  s21::Matrix<double> b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, mult_Matrix3) {
  s21::Matrix<double> a(3, 2);
  s21::Matrix<double> b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a.MulMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, mult_MatrixTotal) {
  s21::Matrix<double> a(3, 2);
  s21::Matrix<double> b(2, 4);
  s21::Matrix<double> res(3, 4);
  double value = 0;
  for (std::size_t i = 0; i < a.GetRows(); i++)
    for (std::size_t j = 0; j < a.GetColumns(); j++) a(i, j) = value++;
  value = 0;
  for (std::size_t i = 0; i < b.GetRows(); i++)
    for (std::size_t j = 0; j < b.GetColumns(); j++) b(i, j) = value++;

  res(0, 0) = 4, res(0, 1) = 5, res(0, 2) = 6, res(0, 3) = 7;
  res(1, 0) = 12, res(1, 1) = 17, res(1, 2) = 22, res(1, 3) = 27;
  res(2, 0) = 20, res(2, 1) = 29, res(2, 2) = 38, res(2, 3) = 47;

  s21::Matrix<double> answer = a * b;
  EXPECT_TRUE(res == answer);
}

TEST(functionalTest, mult_Matrix_Exception) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(s21::Matrix<double> result = a * b);
}

TEST(functionalTest, mult_Matrix_Exception2) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(functionalTest, mult_Matrix_Exception3) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(functionalTest, mult_MatrixNum) {
  s21::Matrix<double> a(3, 2);
  a(1, 1) = 1.1;
  s21::Matrix<double> result = a * 2.;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(functionalTest, mult_MatrixNum2) {
  s21::Matrix<double> a(3, 2);
  a(1, 1) = 1.1;
  a *= 2;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, mult_MatrixNum3) {
  s21::Matrix<double> a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, mult_MatrixNum4) {
  s21::Matrix<double> a(3, 2);
  a.MulNumber(NAN);
  EXPECT_EQ(std::isnan(a(1, 1)), 1);
  EXPECT_EQ(std::isnan(a(2, 1)), 1);
  EXPECT_EQ(std::isnan(a(1, 0)), 1);
}

TEST(functionalTest, equal) {
  s21::Matrix<double> a(2, 3);
  s21::Matrix<double> b(2, 2);
  EXPECT_EQ(a == b, false);
  b.Set(2, 3);
  a(1, 1) = 1.3;
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
  b(1, 2) = 1.3;
  EXPECT_EQ(a == b, false);
}

TEST(functionalTest, equal2) {
  s21::Matrix<double> a(2, 2);
  s21::Matrix<double> b(2, 2);
  EXPECT_EQ(a == b, true);
  a(1, 1) = 1.3;
  EXPECT_EQ(a == b, false);
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
}

TEST(functionalFuncTest, determinant) {
  s21::Matrix<double> basic(4, 4);
  basic(0, 0) = 9;
  basic(0, 1) = 2;
  basic(0, 2) = 2;
  basic(0, 3) = 4;

  basic(1, 0) = 3;
  basic(1, 1) = 4;
  basic(1, 2) = 4;
  basic(1, 3) = 4;

  basic(2, 0) = 4;
  basic(2, 1) = 4;
  basic(2, 2) = 9;
  basic(2, 3) = 9;

  basic(3, 0) = 1;
  basic(3, 1) = 1;
  basic(3, 2) = 5;
  basic(3, 3) = 1;
  EXPECT_DOUBLE_EQ(basic.Determinant(), -578);
}

TEST(functionalFuncTest, determinant2) {
  s21::Matrix<double> basic(1, 1);
  basic(0, 0) = 10;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 10);
}

TEST(functionalFuncTest, determinant3) {
  s21::Matrix<double> basic(2, 2);
  basic(0, 0) = 1.1;
  basic(0, 1) = 3.5;

  basic(1, 0) = -2;
  basic(1, 1) = 4;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 11.4);
}

TEST(functionalFuncTest, determinantException) {
  s21::Matrix<double> exception(4, 3);
  EXPECT_ANY_THROW(exception.Determinant());
}

TEST(functionalFuncTest, inverse_matrix) {
  s21::Matrix<double> basic(3, 3);

  basic(0, 0) = 4;
  basic(0, 1) = -2;
  basic(0, 2) = 1;

  basic(1, 0) = 1;
  basic(1, 1) = 6;
  basic(1, 2) = -2;

  basic(2, 0) = 1;
  basic(2, 1) = 0;
  basic(2, 2) = 0;

  basic = basic.InverseMatrix();

  EXPECT_EQ(basic(0, 1), 0);
  EXPECT_EQ(basic(0, 2), 1);

  EXPECT_EQ(basic(1, 0), 1);
  EXPECT_EQ(basic(2, 0), 3);

  EXPECT_EQ(basic(2, 1), 1);
  EXPECT_EQ(basic(2, 2), -13);
}

TEST(functionalFuncTest, inverse_matrix2) {
  s21::Matrix<double> basic(3, 3);

  basic(0, 0) = 2;
  basic(0, 1) = 2;
  basic(0, 2) = 123;

  basic(1, 0) = 12;
  basic(1, 1) = 6;
  basic(1, 2) = 5;

  basic(2, 0) = 1;
  basic(2, 1) = 2;
  basic(2, 2) = 8;

  basic = basic.InverseMatrix();

  EXPECT_DOUBLE_EQ(basic(0, 1), 0.10910815939278938);
  EXPECT_DOUBLE_EQ(basic(0, 2), -0.34535104364326374);

  EXPECT_DOUBLE_EQ(basic(1, 0), -0.043168880455407968);
  EXPECT_DOUBLE_EQ(basic(2, 0), 0.0085388994307400382);

  EXPECT_DOUBLE_EQ(basic(2, 1), -0.00094876660341555979);
  EXPECT_DOUBLE_EQ(basic(2, 2), -0.0056925996204933585);
}

TEST(functionalFuncTest, inverse_matrixException) {
  s21::Matrix<double> exception(3, 3);

  //  determ = 0
  exception(0, 0) = 1;
  exception(0, 1) = 1;
  exception(0, 2) = 3;
  exception(1, 0) = 4;
  exception(1, 1) = 4;
  exception(1, 2) = 6;
  exception(2, 0) = 4;
  exception(2, 1) = 4;
  exception(2, 2) = 9;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, inverse_matrixException2) {
  s21::Matrix<double> exception(3, 3);

  exception(0, 0) = 1;
  exception(0, 1) = 4;
  exception(0, 2) = 1;
  exception(1, 0) = 3;
  exception(1, 1) = 7;
  exception(1, 2) = 2;
  exception(2, 0) = 3;
  exception(2, 1) = 2;
  exception(2, 2) = 1;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, inverse_matrixException3) {
  s21::Matrix<double> exception(3, 2);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, transpose) {
  s21::Matrix<double> result(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;
  result = result.Transpose();

  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 3);
}

TEST(functionalFuncTest, calc_complements) {
  s21::Matrix<double> result(2, 2);
  s21::Matrix<double> another(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;

  another(0, 0) = 1;
  another(0, 1) = 2;
  another(1, 0) = 13;
  another(1, 1) = 7;

  result -= another * result;
  result = result.CalcComplements();

  EXPECT_EQ(result(0, 0), -44);
  EXPECT_EQ(result(0, 1), 37);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), -8);
}

TEST(functionalFuncTest, calc_complementsException) {
  s21::Matrix<double> exception(4, 3);
  EXPECT_ANY_THROW(exception.CalcComplements().GetRows());
}

TEST(functionalTest, operators_over) {
  s21::Matrix<double> m1(1, 1);
  m1(0, 0) = 2;
  double num = 2;
  s21::Matrix<double> res = num * m1;
  s21::Matrix<double> res2 = m1 * num;
  s21::Matrix<double> res3 = res * res2;
  EXPECT_EQ(res(0, 0), 4);
  EXPECT_EQ(res2(0, 0), 4);
  EXPECT_EQ(res3(0, 0), 16);
}
