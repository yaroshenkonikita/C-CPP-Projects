#include "matrix_oop.h"

Matrix::Matrix() : rows_(3), columns_(3) { matrix_ = new double[9]{0}; }

Matrix::~Matrix() { delete[] matrix_; }

Matrix::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
  if (rows_ <= 0 || columns_ <= 0) {
    throw std::invalid_argument("Arguments cannot be less than one");
  }
  matrix_ = new double[Size()]{0};
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), columns_(other.columns_) {
  matrix_ = new double[Size()]{0};
  std::copy_n(other.matrix_, Size(), matrix_);
}

Matrix::Matrix(Matrix &&other) {
  rows_ = std::exchange(other.rows_, 3);
  columns_ = std::exchange(other.columns_, 3);
  matrix_ = std::exchange(other.matrix_, new double[9]{0});
}

int Matrix::GetColumns() const noexcept { return columns_; }

int Matrix::GetRows() const noexcept { return rows_; }

int Matrix::Size() const noexcept { return columns_ * rows_; }

void Matrix::Set(int size_rows, int size_columns) {
  if (size_rows <= 0 || size_columns <= 0) {
    throw std::invalid_argument("Argument cannot be less than one");
  }
  Matrix temp(size_rows, size_columns);
  for (int i = 0; i < std::min(rows_, size_rows); ++i) {
    for (int j = 0; j < std::min(columns_, size_columns); ++j) {
      temp(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(temp);
}

void Matrix::SetRows(int size_rows) { Set(size_rows, columns_); }

void Matrix::SetColumns(int size_columns) { Set(rows_, size_columns); }

double &Matrix::operator()(const int rows, const int columns) {
  if (rows >= rows_ || columns >= columns_ || rows < 0 || columns < 0) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[rows * columns_ + columns];
}

const double &Matrix::operator()(const int rows, const int columns) const {
  if (rows >= rows_ || columns >= columns_ || rows < 0 || columns < 0) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[rows * columns_ + columns];
}

bool Matrix::EqMatrix(const Matrix &other) const {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    return false;
  }
  std::size_t max_index = Size();
  for (std::size_t i = 0; i < max_index; ++i) {
    if (std::fabs(matrix_[i] - other.matrix_[i]) > 1e-6) {
      return false;
    }
  }
  return true;
}

void Matrix::CheckEqSize(const Matrix &other) const {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    throw std::invalid_argument("Wrong matrix, different Size");
  }
}

void Matrix::SumMatrix(const Matrix &other) {
  CheckEqSize(other);
  for (std::size_t i = 0, max_index = Size(); i < max_index; ++i) {
    matrix_[i] += other.matrix_[i];
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  CheckEqSize(other);
  for (std::size_t i = 0, max_index = Size(); i < max_index; ++i) {
    matrix_[i] -= other.matrix_[i];
  }
}

void Matrix::MulNumber(const double num) {
  for (std::size_t i = 0, max_index = Size(); i < max_index; ++i) {
    matrix_[i] *= num;
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (columns_ != other.rows_) {
    throw std::invalid_argument(
        "Wrong matrix, different Size first matrix "
        "columns and second matrix rows");
  }
  Matrix result(rows_, other.columns_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.columns_; ++j) {
      for (int k = 0; k < columns_; ++k) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

Matrix Matrix::Transpose() const {
  Matrix result(columns_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

Matrix Matrix::MinorMatrix(int discard_row, int discard_column) const {
  if (rows_ <= 1 || columns_ <= 1 || discard_row >= rows_ ||
      discard_column >= columns_) {
    throw std::invalid_argument("Invalid argument, impossible minor matrix");
  }
  Matrix result(rows_ - 1, columns_ - 1);
  for (int i = 0, index_row = 0; i < rows_; ++i) {
    for (int j = 0, index_column = 0; j < columns_; ++j) {
      if (i != discard_row && j != discard_column) {
        result(index_row, index_column++) = (*this)(i, j);
        if (index_column == columns_ - 1) {
          index_row++;
        }
      }
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() const {
  if (rows_ != columns_ || rows_ < 2) {
    throw std::invalid_argument(
        "Impossible calc complements, matrix is not square");
  }
  Matrix result(rows_, columns_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      result(i, j) = MinorMatrix(i, j).Determinant() * pow(-1, i + j);
    }
  }
  return result;
}

double Matrix::Determinant() const {
  if (rows_ != columns_) {
    throw std::invalid_argument(
        "Impossible determinant matrix, matrix is not square");
  }
  if (rows_ == 1) {
    return matrix_[0];
  } else if (rows_ == 2) {
    return matrix_[0] * matrix_[3] - matrix_[1] * matrix_[2];
  }
  double determinant = 0.0;
  for (int j = 0; j < rows_; ++j) {
    determinant += matrix_[j] * MinorMatrix(0, j).Determinant() * pow(-1, j);
  }
  return determinant;
}

Matrix Matrix::InverseMatrix() const {
  double det = Determinant();
  if (fabs(det) < 1e-6) {
    throw std::invalid_argument("Impossible inverse matrix, determinant is 0");
  }
  Matrix temp = CalcComplements().Transpose();
  return temp *= 1 / det;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  return SumMatrix(other), *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  return MulMatrix(other), *this;
}

Matrix &Matrix::operator*=(const double num) {
  return MulNumber(num), *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  return SubMatrix(other), *this;
}

bool Matrix::operator==(const Matrix &other) const {
  return EqMatrix(other);
}

bool Matrix::operator!=(const Matrix &other) const {
  return !EqMatrix(other);
}

Matrix Matrix::operator+(const Matrix &other) const {
  Matrix result(*this);
  return result += other;
}

Matrix Matrix::operator-(const Matrix &other) const {
  Matrix result(*this);
  return result -= other;
}

Matrix Matrix::operator*(const Matrix &other) const {
  Matrix result(*this);
  return result *= other;
}

Matrix operator*(double num, Matrix &other) {
  Matrix result(other);
  return result *= num;
}

Matrix operator*(Matrix &other, double num) {
  Matrix result(other);
  return result *= num;
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    Matrix temp(other.rows_, other.columns_);
    std::copy_n(other.matrix_, other.Size(), temp.matrix_);
    *this = std::move(temp);
  }
  return *this;
}

Matrix &Matrix::operator=(Matrix &&other) {
  if (this != &other) {
    delete matrix_;
    rows_ = std::exchange(other.rows_, 3);
    columns_ = std::exchange(other.columns_, 3);
    matrix_ = std::exchange(other.matrix_, new double[9]{0});
  }
  return *this;
}
