#include <gtest/gtest.h>

#include <cstdio>
#include <iostream>

#include "s21_matrix_oop.h"

// void Print(S21Matrix m) {
//   printf("rows %d cols %d\n", m.GetRows(), m.GetCols());
//   for (int i = 0; i < m.GetRows(); i++) {
//     for (int j = 0; j < m.GetCols(); j++)
//       std::cout << (m(i, j) < EPS ? 0 : m(i, j)) << "\t";
//     std::cout << "\n";
//   }
//   std::cout << "---------------------"
//             << "\n";
// }

TEST(constructor, constructor1) {
  S21Matrix a;
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
}

TEST(constructor, constructor2) {
  S21Matrix a(1, 10);
  EXPECT_EQ(a.GetRows(), 1);
  EXPECT_EQ(a.GetCols(), 10);
}

TEST(constructor, constructor3) { EXPECT_ANY_THROW(S21Matrix a(-5, 1)); }

TEST(constructor, constructor4) {
  S21Matrix a(3, 3);
  S21Matrix b(a);
  EXPECT_EQ(a == b, true);
}

TEST(constructor, constructor5) {
  S21Matrix a(3, 4);
  S21Matrix b = std::move(a);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetCols(), 4);
  EXPECT_EQ(a == b, false);
}

TEST(constructor, constructor6) {
  S21Matrix a(3, 4);
  S21Matrix b;
  b = std::move(a);
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetCols(), 4);
  EXPECT_EQ(a == b, false);
}

TEST(operators, index1) {
  S21Matrix a(3, 3);
  a(1, 1) = 3;
  EXPECT_DOUBLE_EQ(a(1, 1), 3);
}

TEST(operators, index2) {
  S21Matrix a(1, 1);
  EXPECT_ANY_THROW(a(1, 5));
}

TEST(operators, copy) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1;
  b(1, 1) = 2;
  a = b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2);
}

TEST(operators, sum1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1;
  b(1, 1) = 2;
  S21Matrix c = a + b;
  EXPECT_DOUBLE_EQ(c(1, 1), 3);
}

TEST(operators, sum2) {
  S21Matrix a(1, 2);
  S21Matrix b(2, 1);
  EXPECT_ANY_THROW(S21Matrix c = a + b);
}

TEST(operators, sum3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1;
  b(1, 1) = 2;
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 3);
}

TEST(operators, sum4) {
  S21Matrix a(1, 2);
  S21Matrix b(2, 1);
  EXPECT_ANY_THROW(a += b);
}

TEST(operators, sum5) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1;
  b(1, 1) = 2;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 3);
}

TEST(operators, sum6) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(operators, sub1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1;
  b(1, 1) = 1;
  S21Matrix c = a - b;
  EXPECT_DOUBLE_EQ(c(1, 1), 0);
}

TEST(operators, sub2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_ANY_THROW(S21Matrix c = a + b);
}

TEST(operators, sub3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1;
  b(1, 1) = 1;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 0);
}

TEST(operators, sub4) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_ANY_THROW(a -= b);
}

TEST(operators, sub5) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1;
  b(1, 1) = 1;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 0);
}

TEST(operators, sub6) {
  S21Matrix a(1, 2);
  S21Matrix b(2, 1);
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(operators, sub7) {
  S21Matrix a(1, 2);
  S21Matrix b(2, 1);
  EXPECT_ANY_THROW(a - b);
}

TEST(operators, mul1) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 2;
  b(1, 1) = 2;
  S21Matrix c = a * b;
  EXPECT_DOUBLE_EQ(c(1, 1), 4);
}

TEST(operators, mul2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_ANY_THROW(S21Matrix c = a * b);
}

TEST(operators, mul3) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 2;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 4);
}

TEST(operators, mul4) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 3);
  EXPECT_ANY_THROW(a *= b);
}

TEST(operators, mul5) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 2;
  b(1, 1) = 2;
  a.MulMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 4);
}

TEST(operators, mul6) {
  S21Matrix a(2, 3);
  S21Matrix b(1, 1);
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(operators, mul7) {
  S21Matrix a(3, 2);
  a(1, 1) = 3;
  S21Matrix c = a * 2;
  EXPECT_DOUBLE_EQ(c(1, 1), 6);
}

TEST(operators, mul8) {
  S21Matrix a(2, 2);
  a(1, 1) = 2;
  a *= 2;
  EXPECT_DOUBLE_EQ(a(1, 1), 4);
}

TEST(operators, mul9) {
  S21Matrix a(2, 2);
  a(1, 1) = 2;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 4);
}

TEST(operators, equal1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, true);
  b(1, 1) = 1;
  EXPECT_EQ(a == b, false);
}

TEST(operators, equal2) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  EXPECT_EQ(a.EqMatrix(b), true);
  b(1, 1) = 1;
  EXPECT_EQ(a.EqMatrix(b), false);
}

TEST(operators, equal3) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  EXPECT_EQ(a != b, false);
}

TEST(functions, setget) {
  S21Matrix a(3, 3);
  a.SetRows(4);
  EXPECT_EQ(a.GetRows(), 4);
  EXPECT_EQ(a.GetCols(), 3);
  a.SetCols(4);
  EXPECT_EQ(a.GetRows(), 4);
  EXPECT_EQ(a.GetCols(), 4);
}
TEST(functions, determinant1) {
  S21Matrix b(1, 1);
  b(0, 0) = 1;
  EXPECT_EQ(b.Determinant(), 1);
}

TEST(functions, determinant2) {
  S21Matrix a(3, 3);
  a(0, 0) = 0;
  a(0, 1) = -1;
  a(0, 2) = 0;
  a(1, 0) = 1;
  a(1, 1) = 3;
  a(1, 2) = -2;
  a(2, 0) = 2;
  a(2, 1) = 5;
  a(2, 2) = -1;
  EXPECT_EQ(a.Determinant(), 3);
}

TEST(functions, determinant3) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;
  EXPECT_EQ(a.Determinant(), 0);
}

TEST(functions, determinant4) {
  S21Matrix m(1, 2);
  EXPECT_ANY_THROW(m.Determinant());
}

TEST(functions, transpose) {
  S21Matrix A(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;

  S21Matrix B = A.Transpose();
  EXPECT_EQ(B(0, 0), 1);
  EXPECT_EQ(B(1, 0), 2);
  EXPECT_EQ(B(2, 0), 3);
  EXPECT_EQ(B(0, 1), 4);
  EXPECT_EQ(B(1, 1), 5);
  EXPECT_EQ(B(2, 1), 6);
}

TEST(functions, complements1) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;

  b(0, 0) = 0;
  b(0, 1) = 10;
  b(0, 2) = -20;
  b(1, 0) = 4;
  b(1, 1) = -14;
  b(1, 2) = 8;
  b(2, 0) = -8;
  b(2, 1) = -2;
  b(2, 2) = 4;

  S21Matrix c = a.CalcComplements();
  EXPECT_EQ(c == b, true);
}

TEST(functions, complements2) {
  S21Matrix m(1, 2);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(functions, inverse) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);

  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;
  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;
  a(2, 0) = 5;
  a(2, 1) = -2;
  a(2, 2) = -3;

  b(0, 0) = 1;
  b(0, 1) = -1;
  b(0, 2) = 1;
  b(1, 0) = -38;
  b(1, 1) = 41;
  b(1, 2) = -34;
  b(2, 0) = 27;
  b(2, 1) = -29;
  b(2, 2) = 24;

  S21Matrix c = a.InverseMatrix();
  EXPECT_EQ(c == b, true);
}

TEST(functions, inverse2) {
  S21Matrix m(3, 3);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m(2, 0) = 7;
  m(2, 1) = 8;
  m(2, 2) = 9;

  EXPECT_EQ(m.Determinant(), 0);
  EXPECT_ANY_THROW(m.InverseMatrix());
}

TEST(functions, inverse3) {
  S21Matrix m(3, 2);
  EXPECT_ANY_THROW(m.InverseMatrix());
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
