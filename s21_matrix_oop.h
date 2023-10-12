#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#define EPS 1e-7

#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  int GetCols() { return cols_; }
  int GetRows() { return rows_; }
  void SetCols(const int cols);
  void SetRows(const int rows);

  double &operator()(int row, int col);
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double number) const;
  bool operator==(const S21Matrix &other) noexcept;
  bool operator!=(const S21Matrix &other) noexcept;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double number);
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix Minor(int row, int column) const;
  S21Matrix InverseMatrix() const;
  void Resize(int rows, int cols);
};

#endif  // SRC_MATRIX_H_