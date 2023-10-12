#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1)
    throw std::invalid_argument("rows/cols incorrect");

  matrix_ = (double **)new double *[rows_];

  for (int i = 0; i < rows_; i++) matrix_[i] = (double *)new double[cols_];

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) matrix_[i][j] = 0;
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = (double **)new double *[rows_];

  for (int i = 0; i < rows_; i++) matrix_[i] = (double *)new double[cols_];

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
}

S21Matrix::~S21Matrix() {
  if (cols_ > 0) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  }

  if (rows_ > 0) delete[] matrix_;

  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::operator==(const S21Matrix &other) noexcept {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix &other) noexcept {
  return !EqMatrix(other);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = true;
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    res = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) >= EPS) {
          res = false;
          break;
        }
      }
      if (!res) break;
    }
  }
  return res;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::invalid_argument("rows/cols incorrect");
  }
  return matrix_[row][col];
}

void S21Matrix::SetCols(const int cols) {
  if (cols < 1) {
    throw std::invalid_argument("cols incorrect");
  }
  Resize(rows_, cols);
}

void S21Matrix::SetRows(const int rows) {
  if (rows < 1) {
    throw std::invalid_argument("rows incorrect");
  }
  Resize(rows, cols_);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    Resize(other.rows_, other.cols_);
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }

  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result{*this};
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result{*this};
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result{*this};
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result{*this};
  result.MulNumber(num);
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    throw std::logic_error("rows or cols not equal");
  }

  S21Matrix tmp(other);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += tmp(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (other.rows_ != rows_ || other.cols_ != cols_) {
    throw std::logic_error("rows or cols not equal");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("rows/cols mismatch");
  }
  S21Matrix result{rows_, other.cols_};
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) += (*this)(i, k) * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::Resize(int rows, int cols) {
  double **matrix = (double **)new double *[rows];

  for (int i = 0; i < rows; i++) matrix[i] = (double *)new double[cols];

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) matrix[i][j] = 0;

  for (int i = 0; i < rows_ && i < rows; i++)
    for (int j = 0; j < cols_ && j < cols; j++) matrix[i][j] = matrix_[i][j];

  if (cols_ > 0) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  }

  if (rows_ > 0) delete[] matrix_;

  matrix_ = matrix;
  rows_ = rows;
  cols_ = cols;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::Minor(int row, int column) const {
  S21Matrix minor{rows_ - 1, cols_ - 1};

  int di = 0, dj = 0;

  for (int i = 0; i < rows_ - 1; i++) {
    if (i == row) di = 1;
    dj = 0;

    for (int j = 0; j < cols_ - 1; j++) {
      if (j == column) dj = 1;
      minor(i, j) = matrix_[i + di][j + dj];
    }
  }

  return minor;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result{rows_, cols_};

  if (rows_ != cols_) {
    throw std::logic_error("matrix not square");
  }

  if (rows_ == 1) {
    result(0, 0) = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor = Minor(i, j);
        int sign = ((i + j) % 2 == 0) ? 1 : -1;
        result(i, j) = minor.Determinant() * sign;
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("matrix not square");
  }

  double det = Determinant();
  if (std::fabs(det) < EPS) {
    throw std::logic_error("zero determinant");
  }

  S21Matrix result = CalcComplements().Transpose();
  result *= (1 / det);

  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("matrix not square");
  }
  int n = rows_;
  double c, mul, max, a[n][n];
  int i, j, k, r;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      a[i][j] = matrix_[i][j];
    }
  double det = 1;

  for (k = 0; k < n; k++) {
    max = abs(a[k][k]);
    r = k;
    for (i = k + 1; i < n; i++)
      if (abs(a[i][k]) > max) {
        max = abs(a[i][k]);
        r = i;
      }
    if (r != k) det = -det;
    for (j = 0; j < n; j++) {
      c = a[k][j];
      a[k][j] = a[r][j];
      a[r][j] = c;
    }
    for (i = k + 1; i < n; i++)
      for (mul = a[i][k] / a[k][k], j = k; j < n; j++) a[i][j] -= mul * a[k][j];
  }
  for (i = 0; i < n; i++) det *= a[i][i];
  return det;
}