#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <memory>
#include <limits>

namespace s21 {

template<class T>
class Matrix {
 public:
  Matrix() : rows_(3), columns_(3), matrix_(new T[9]{}) {}
  ~Matrix() {}
  Matrix(std::size_t rows, std::size_t columns) : rows_(rows), columns_(columns) {
    if (!rows_ || !columns_) {
      throw std::invalid_argument("Arguments cannot be zero");
    } else if (Size() >= std::numeric_limits<T>::max()) {
      throw std::invalid_argument("Over valueeric limits");
    }
    matrix_ = new T[Size()]{};
  }
  Matrix(const Matrix &other) : rows_(other.rows_), columns_(other.columns_) {
    matrix_ = new T[Size()]{};
    std::copy_n(other.matrix_, Size(), matrix_);
  }
  Matrix(Matrix &&other) {
    rows_ = std::exchange(other.rows_, 3);
    columns_ = std::exchange(other.columns_, 3);
    matrix_ = std::exchange(other.matrix_, new T[9]{0});
  }

  std::size_t GetColumns() const noexcept { return columns_; }
  std::size_t GetRows() const noexcept { return rows_; }
  std::uint64_t Size() const noexcept { return columns_ * rows_; }

  void Set(std::size_t rows, std::size_t columns) {
    Matrix temp(rows, columns);
    for (std::size_t row = 0; row < std::min(rows_, rows); ++row) {
      for (std::size_t column = 0; column < std::min(columns_, columns); ++column) {
        temp(row, column) = (*this)(row, column);
      }
    }
    *this = std::move(temp);
  }
  void SetRows(const std::size_t rows) { Set(rows, columns_); }
  void SetColumns(const std::size_t columns) { Set(rows_, columns); }
  
  T &operator()(const std::size_t rows, const std::size_t columns) {
    if (rows >= rows_ || columns >= columns_) {
      throw std::out_of_range("Index out of range");
    }
    return matrix_[rows * columns_ + columns];
  }
  const T &operator()(const std::size_t rows, const std::size_t columns) const {
    if (rows >= rows_ || columns >= columns_) {
      throw std::out_of_range("Index out of range");
    }
    return matrix_[rows * columns_ + columns];
  }

  Matrix &operator+=(const Matrix &other) { return SumMatrix(other), *this; }
  Matrix &operator*=(const Matrix &other) { return MulMatrix(other), *this; }
  Matrix &operator*=(const T &value) { return Mulvalueber(value), *this; }
  Matrix &operator-=(const Matrix &other) { return SubMatrix(other), *this; }

  bool operator==(const Matrix &other) const { return EqMatrix(other); }
  bool operator!=(const Matrix &other) const { return !EqMatrix(other); }

  [[nodiscard]] Matrix operator+(Matrix other) const { return other += *this; }
  [[nodiscard]] Matrix operator-(Matrix other) const { return other -= *this; }
  [[nodiscard]] Matrix operator*(Matrix other) const { return other *= *this; }

  Matrix &operator=(const Matrix &other) {
    if (this != &other) {
      Matrix temp(other);
      *this = std::move(temp);
    }
    return *this;
  }
  Matrix &operator=(Matrix &&other) {
    if (this != &other) {
      rows_ = std::exchange(other.rows_, 3);
      columns_ = std::exchange(other.columns_, 3);
      matrix_.reset(std::exchange(other.matrix_, new T[9]{0}));
    }
    return *this;
  }

  bool EqMatrix(const Matrix &other) const {
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

  void SumMatrix(const Matrix &other) {
    CheckEqSize(other);
    for (std::uint64_t i = 0, max_index = Size(); i < max_index; ++i) {
      matrix_[i] += other.matrix_[i];
    }
  }
  void SubMatrix(const Matrix &other) {
    CheckEqSize(other);
    for (std::uint64_t i = 0, max_index = Size(); i < max_index; ++i) {
      matrix_[i] -= other.matrix_[i];
    }
  }
  void Mulvalueber(const T value) {
    for (std::uint64_t i = 0, max_index = Size(); i < max_index; ++i) {
      matrix_[i] *= value;
    }
  }
  void MulMatrix(const Matrix &other) {
    if (columns_ != other.rows_) {
      throw std::invalid_argument(
          "Wrong matrix, different Size first matrix "
          "columns and second matrix rows");
    }
    Matrix result(rows_, other.columns_);
    for (std::size_t i = 0; i < result.rows_; ++i) {
      for (std::size_t j = 0; j < result.columns_; ++j) {
        for (std::size_t k = 0; k < columns_; ++k) {
          result(i, j) += (*this)(i, k) * other(k, j);
        }
      }
    }
    *this = std::move(result);
  }

  [[nodiscard]] Matrix Transpose() const {
    Matrix result(columns_, rows_);
    for (std::size_t i = 0; i < rows_; ++i) {
      for (std::size_t j = 0; j < columns_; ++j) {
        result(j, i) = (*this)(i, j);
      }
    }
    return result;
  }
  [[nodiscard]] Matrix MinorMatrix(std::size_t discard_row, std::size_t discard_column) const {
    if (rows_ == 1 || columns_ == 1 || discard_row >= rows_ || discard_column >= columns_) {
      throw std::invalid_argument("Invalid argument, impossible minor matrix");
    }
    Matrix result(rows_ - 1, columns_ - 1);
    for (int i = 0, index_row = 0; i < rows_; ++i) {
      for (int j = 0, index_column = 0; j < columns_; ++j) {
        if (i == discard_row || j == discard_column) continue;
        result(index_row, index_column++) = (*this)(i, j);
      }
      if (i != discard_row) { index_row++; }
    }
    return result;
  }
  [[nodiscard]] Matrix CalcComplements() const {
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
  T Determinant() const {
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
    for (int j = 0; j < rows_; ++j) {
      determinant += matrix_[j] * MinorMatrix(0, j).Determinant() * pow(-1, j);
    }
    return determinant;
  }
  [[nodiscard]] Matrix InverseMatrix() const {
    T det = Determinant();
    if (fabs(det) < 1e-6) {
      throw std::invalid_argument("Impossible inverse matrix, determinant is 0");
    }
    Matrix temp = CalcComplements().Transpose();
    return temp *= 1 / det;
  }

 private:
  std::shared_ptr<T> matrix_;
  std::size_t rows_, columns_;
  
  void CheckEqSize(const Matrix &other) const {
    if (rows_ != other.rows_ || columns_ != other.columns_) {
      throw std::invalid_argument("Wrong matrix, different Size");
    }
  }
};

template<class T>
Matrix<T> operator*(T value, Matrix<T> other) { return other += value; }
template<class T>
Matrix<T> operator*(Matrix<T> other, T value) { return other += value; }

} // namespase s21
