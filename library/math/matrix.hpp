#pragma once

#include <cassert>
#include <vector>

using namespace std;

namespace yz {

template <class T>
struct Matrix {
  vector<vector<T>> a;

  Matrix() {}

  Matrix(int n, int m, T value = T()) : a(n, vector<T>(m, value)) {}

  explicit Matrix(int n, T value = T()) : a(n, vector<T>(n, value)) {}

  const vector<T> &operator[](int i) const {
    return a[i];
  }

  vector<T> &operator[](int i) {
    return a[i];
  }

  static Matrix identity(int n) {
    Matrix res(n);
    for (int i = 0; i < n; i++) res[i][i] = T(1);
    return res;
  }

  Matrix &operator+=(const Matrix &other) {
    int n = a.size(), m = a[0].size();
    assert(n == static_cast<int>(other.a.size()));
    assert(m == static_cast<int>(other.a[0].size()));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        a[i][j] += other[i][j];
      }
    }
    return *this;
  }

  Matrix &operator-=(const Matrix &other) {
    int n = a.size(), m = a[0].size();
    assert(n == static_cast<int>(other.a.size()));
    assert(m == static_cast<int>(other.a[0].size()));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        a[i][j] -= other[i][j];
      }
    }
    return *this;
  }

  Matrix &operator*=(const Matrix &other) {
    int n = a.size(), m = other.a[0].size(), p = a[0].size();
    assert(p == static_cast<int>(other.a.size()));
    Matrix res(n, m);
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < p; k++) {
        for (int j = 0; j < m; j++) {
          res[i][j] += a[i][k] * other[k][j];
        }
      }
    }
    a.swap(res.a);
    return *this;
  }

  Matrix &operator^=(long long exponent) {
    assert(a.size() == a[0].size());
    assert(exponent >= 0);
    Matrix base(*this);
    Matrix res = identity(a.size());
    while (exponent > 0) {
      if (exponent & 1) res *= base;
      base *= base;
      exponent >>= 1;
    }
    a.swap(res.a);
    return *this;
  }

  Matrix operator+(const Matrix &other) const {
    return Matrix(*this) += other;
  }

  Matrix operator-(const Matrix &other) const {
    return Matrix(*this) -= other;
  }

  Matrix operator*(const Matrix &other) const {
    return Matrix(*this) *= other;
  }

  Matrix operator^(long long exponent) const {
    return Matrix(*this) ^= exponent;
  }
};

}  // namespace yz
