#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace s21 {

template <class T>
class Matrix {
 public:
  Matrix();
  ~Matrix();
  Matrix(std::size_t rows, std::size_t columns);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);

  std::size_t GetColumns() const noexcept;
  std::size_t GetRows() const noexcept;
  std::uint64_t Size() const noexcept;

  void Set(std::size_t rows, std::size_t columns);
  void SetRows(const std::size_t rows);
  void SetColumns(const std::size_t columns);

  T &operator()(const std::size_t rows, const std::size_t columns) const;

  Matrix &operator+=(const Matrix &other);
  Matrix &operator*=(const Matrix &other);
  Matrix &operator*=(const T &value);
  Matrix &operator-=(const Matrix &other);

  bool operator==(const Matrix &other) const;
  bool operator!=(const Matrix &other) const;

  [[nodiscard]] Matrix operator+(Matrix other) const;
  [[nodiscard]] Matrix operator-(const Matrix &other) const;
  [[nodiscard]] Matrix operator*(const Matrix &other) const;

  Matrix &operator=(const Matrix &other);
  Matrix &operator=(Matrix &&other);

  bool EqMatrix(const Matrix &other) const;

  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const T value);
  void MulMatrix(const Matrix &other);

  [[nodiscard]] Matrix Transpose() const;
  [[nodiscard]] Matrix MinorMatrix(std::size_t discard_row,
                                   std::size_t discard_column) const;
  [[nodiscard]] Matrix CalcComplements() const;
  T Determinant() const;
  [[nodiscard]] Matrix InverseMatrix() const;

 private:
  void CheckEqSize(const Matrix &other) const;

  std::size_t rows_, columns_;
  T *matrix_;
};

template <class T>
Matrix<T>::Matrix() : rows_(3), columns_(3), matrix_(new T[9]{}) {}

template <class T>
Matrix<T>::~Matrix() { delete[] matrix_; }

template <class T>
Matrix<T>::Matrix(std::size_t rows, std::size_t columns)
    : rows_(rows), columns_(columns) {
  if (!rows_ || !columns_) {
    throw std::invalid_argument("Arguments cannot be zero");
  } else if (Size() >= std::numeric_limits<T>::max()) {
    throw std::invalid_argument("Over valueeric limits");
  }
  matrix_ = new T[Size()]{};
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &other)
    : rows_(other.rows_), columns_(other.columns_) {
  matrix_ = new T[Size()]{};
  std::copy_n(other.matrix_, Size(), matrix_);
}

template <class T>
Matrix<T>::Matrix(Matrix<T> &&other) {
  rows_ = std::exchange(other.rows_, 3);
  columns_ = std::exchange(other.columns_, 3);
  matrix_ = std::exchange(other.matrix_, new T[9]{0});
}

template <class T>
std::size_t Matrix<T>::GetColumns() const noexcept {
  return columns_;
}

template <class T>
std::size_t Matrix<T>::GetRows() const noexcept {
  return rows_;
}

template <class T>
std::uint64_t Matrix<T>::Size() const noexcept {
  return columns_ * rows_;
}

template <class T>
void Matrix<T>::Set(std::size_t rows, std::size_t columns) {
  Matrix<T> temp(rows, columns);
  for (std::size_t row = 0; row < std::min(rows_, rows); ++row) {
    for (std::size_t column = 0; column < std::min(columns_, columns);
         ++column) {
      temp(row, column) = (*this)(row, column);
    }
  }
  *this = std::move(temp);
}

template <class T>
void Matrix<T>::SetRows(const std::size_t rows) {
  Set(rows, columns_);
}

template <class T>
void Matrix<T>::SetColumns(const std::size_t columns) {
  Set(rows_, columns);
}

template <class T>
T &Matrix<T>::operator()(const std::size_t rows,
                               const std::size_t columns) const {
  if (rows >= rows_ || columns >= columns_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[rows * columns_ + columns];
}

template <class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other) {
  return SumMatrix(other), *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other) {
  return MulMatrix(other), *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator*=(const T &value) {
  return MulNumber(value), *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other) {
  return SubMatrix(other), *this;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T> &other) const {
  return EqMatrix(other);
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T> &other) const {
  return !EqMatrix(other);
}

template <class T>
[[nodiscard]] Matrix<T> Matrix<T>::operator+(Matrix<T> other) const {
  return other += *this;
}

template <class T>
[[nodiscard]] Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const {
  Matrix<T> copy_this(*this);
  return copy_this -= other;
}

template <class T>
[[nodiscard]] Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
  Matrix<T> copy_this(*this);
  return copy_this *= other;
}

template <class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
  if (this != &other) {
    Matrix<T> temp(other);
    *this = std::move(temp);
  }
  return *this;
}

template <class T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) {
  if (this != &other) {
    delete[] matrix_;
    rows_ = std::exchange(other.rows_, 3);
    columns_ = std::exchange(other.columns_, 3);
    matrix_ = std::exchange(other.matrix_, new T[9]{0});
  }
  return *this;
}

template <class T>
bool Matrix<T>::EqMatrix(const Matrix<T> &other) const {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    return false;
  }
  for (std::uint64_t i = 0, max_index = Size(); i < max_index; ++i) {
    if (matrix_[i] != other.matrix_[i]) {
      return false;
    }
  }
  return true;
}

template <class T>
void Matrix<T>::SumMatrix(const Matrix<T> &other) {
  CheckEqSize(other);
  for (std::uint64_t i = 0, max_index = Size(); i < max_index; ++i) {
    matrix_[i] += other.matrix_[i];
  }
}

template <class T>
void Matrix<T>::SubMatrix(const Matrix<T> &other) {
  CheckEqSize(other);
  for (std::uint64_t i = 0, max_index = Size(); i < max_index; ++i) {
    matrix_[i] -= other.matrix_[i];
  }
}

template <class T>
void Matrix<T>::MulNumber(const T value) {
  for (std::uint64_t i = 0, max_index = Size(); i < max_index; ++i) {
    matrix_[i] *= value;
  }
}

template <class T>
void Matrix<T>::MulMatrix(const Matrix<T> &other) {
  if (this->columns_ != other.rows_) {
    throw std::invalid_argument(
        "Wrong matrix, different Size first matrix "
        "columns and second matrix rows");
  }
  Matrix<T> result(rows_, other.columns_);
  for (std::size_t i = 0; i < result.rows_; ++i) {
    for (std::size_t j = 0; j < result.columns_; ++j) {
      for (std::size_t k = 0; k < columns_; ++k) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

template <class T>
[[nodiscard]] Matrix<T> Matrix<T>::Transpose() const {
  Matrix<T> result(columns_, rows_);
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < columns_; ++j) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

template <class T>
[[nodiscard]] Matrix<T> Matrix<T>::MinorMatrix(
    std::size_t discard_row, std::size_t discard_column) const {
  if (rows_ == 1 || columns_ == 1 || discard_row >= rows_ ||
      discard_column >= columns_) {
    throw std::invalid_argument("Invalid argument, impossible minor matrix");
  }
  Matrix<T> result(rows_ - 1, columns_ - 1);
  for (std::size_t i = 0, index_row = 0; i < rows_; ++i) {
    for (std::size_t j = 0, index_column = 0; j < columns_; ++j) {
      if (i == discard_row || j == discard_column) continue;
      result(index_row, index_column++) = (*this)(i, j);
    }
    if (i != discard_row) {
      index_row++;
    }
  }
  return result;
}

template <class T>
[[nodiscard]] Matrix<T> Matrix<T>::CalcComplements() const {
  if (rows_ != columns_ || rows_ < 2) {
    throw std::invalid_argument(
        "Impossible calc complements, matrix is not square");
  }
  Matrix<T> result(rows_, columns_);
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < columns_; ++j) {
      result(i, j) = MinorMatrix(i, j).Determinant() * pow(-1, i + j);
    }
  }
  return result;
}

template <class T>
T Matrix<T>::Determinant() const {
  if (rows_ != columns_) {
    throw std::invalid_argument(
        "Impossible determinant matrix, matrix is not square");
  }
  if (rows_ == 1) {
    return matrix_[0];
  } else if (rows_ == 2) {
    return matrix_[0] * matrix_[3] - matrix_[1] * matrix_[2];
  }
  T determinant = 0.0;
  for (std::size_t j = 0; j < rows_; ++j) {
    determinant += matrix_[j] * MinorMatrix(0, j).Determinant() * pow(-1, j);
  }
  return determinant;
}

template <class T>
[[nodiscard]] Matrix<T> Matrix<T>::InverseMatrix() const {
  T det = Determinant();
  if (fabs(det) < 1e-6) {
    throw std::invalid_argument("Impossible inverse matrix, determinant is 0");
  }
  Matrix<T> temp = CalcComplements().Transpose();
  return temp *= 1 / det;
}

template <class T>
void Matrix<T>::CheckEqSize(const Matrix &other) const {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    throw std::invalid_argument("Wrong matrix, different Size");
  }
}

template <class T>
Matrix<T> operator*(T value, Matrix<T> other) {
  return other *= value;
}

template <class T>
Matrix<T> operator*(Matrix<T> other, T value) {
  return other *= value;
}

}  // namespace s21
