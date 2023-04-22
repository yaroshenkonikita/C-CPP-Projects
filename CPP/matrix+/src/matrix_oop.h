#include <algorithm>
#include <cmath>
#include <stdexcept>

class Matrix {
 public:
  // Default constructor
  Matrix();
  // Destructor
  ~Matrix();
  // Parameterized constructor
  Matrix(int Rows, int Columns);
  // Copy constructor
  Matrix(const Matrix &other);
  // Move constructor
  Matrix(Matrix &&other);

  // Accessors
  int GetColumns() const noexcept;
  int GetRows() const noexcept;
  // Elements in Matrix
  int Size() const noexcept;

  // Mutator
  void Set(int size_rows, int size_columns);
  void SetRows(int size_rows);
  void SetColumns(int size_columns);
  
  // Matrix indexing
  // Set
  double &operator()(const int rows, const int columns);
  // Get
  const double &operator()(const int rows, const int columns) const;

  // Operator equivalent to SumMatrix
  Matrix &operator+=(const Matrix &other);
  // Operator equivalent to MulMatrix
  Matrix &operator*=(const Matrix &other);
  // Operator equivalent to MulNumber
  Matrix &operator*=(double num);
  // Operator equivalent to SubMatrix
  Matrix &operator-=(const Matrix &other);

  // Operators equivalent to EqMatrix
  bool operator==(const Matrix &other) const;
  // Operators equivalent to !EqMatrix
  bool operator!=(const Matrix &other) const;

  // Addition of two matrices
  [[nodiscard]] Matrix operator+(const Matrix &other) const;
  // Subtraction of one matrix from another
  [[nodiscard]] Matrix operator-(const Matrix &other) const;
  // Matrix multiplication
  [[nodiscard]] Matrix operator*(const Matrix &other) const;
  // Мatrix multiplication by a number
  [[nodiscard]] friend Matrix operator*(double num, Matrix &other);
  [[nodiscard]] friend Matrix operator*(Matrix &other, double num);

  // Сopying of values from one matrix to another one
  Matrix &operator=(const Matrix &other);
  // Move values from one matrix to another
  Matrix &operator=(Matrix &&other);

  // Checks matrices for equality with each other
  bool EqMatrix(const Matrix &other) const;

  // Adds the second matrix to the current one
  void SumMatrix(const Matrix &other);
  // Subtracts another matrix from the current one
  void SubMatrix(const Matrix &other);
  // Multiplies the current matrix by a number
  void MulNumber(double num);
  // Multiplies the current matrix by the second matrix
  void MulMatrix(const Matrix &other);

  // Creates a new transposed matrix from the current one and returns it
  [[nodiscard]] Matrix Transpose() const;
  // Creates a new minor matrix from the current one and returns it
  [[nodiscard]] Matrix MinorMatrix(int discard_row,
                                      int discard_column) const;
  // Calculates the algebraic addition matrix of the current one and returns it
  [[nodiscard]] Matrix CalcComplements() const;
  // Calculates and returns the determinant of the current matrix
  double Determinant() const;
  // Calculates and returns the inverse matrix
  [[nodiscard]] Matrix InverseMatrix() const;

 private:
  // Attributes
  double *matrix_;
  int rows_, columns_;
  
  // Check on equal size
  void CheckEqSize(const Matrix &other) const;

};
