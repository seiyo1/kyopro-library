# Matrix

行列の加算、減算、積、累乗を扱います。

## Usage

```cpp
yz::Matrix<long long> a(2, 2);
a[0][0] = 1;
a[0][1] = 1;
a[1][0] = 1;
a[1][1] = 0;

auto b = a ^ 10;
auto id = yz::Matrix<long long>::identity(2);
```

## メンバー変数

- `vector<vector<T>> a`
    - 行列の中身です。
    - `a[i][j]` が `i` 行 `j` 列の値です。

## コンストラクタ

- `Matrix()`
    - 空の行列を作ります。

- `Matrix(int n, int m, T value = T())`
    - `n` 行 `m` 列の行列を作ります。
    - 初期値は `value` です。
    - `value` を省略すると `T()` で初期化されます。

- `Matrix(int n, T value = T())`
    - `n` 行 `n` 列の正方行列を作ります。
    - 初期値は `value` です。

## 関数

- `const vector<T> &operator[](int i) const`
    - `i` 行目の `vector<T>` を読み取り専用で返します。
    - `const Matrix` に対して `mat[i][j]` の形で要素にアクセスできます。

- `vector<T> &operator[](int i)`
    - `i` 行目の `vector<T>` を返します。
    - `mat[i][j]` の形で要素の読み書きができます。

- `static Matrix identity(int n)`
    - `n` 行 `n` 列の単位行列を返します。

- `Matrix &operator+=(const Matrix &other)`
    - 自分自身に `other` を足します。
    - 行数と列数が一致している必要があります。

- `Matrix &operator-=(const Matrix &other)`
    - 自分自身から `other` を引きます。
    - 行数と列数が一致している必要があります。

- `Matrix &operator*=(const Matrix &other)`
    - 自分自身に `other` を右から掛けます。
    - 自分の列数と `other` の行数が一致している必要があります。

- `Matrix &operator^=(long long exponent)`
    - 自分自身を `exponent` 乗します。
    - 正方行列である必要があります。
    - `exponent` は `0` 以上である必要があります。

- `Matrix operator+(const Matrix &other) const`
    - `this + other` の結果を返します。

- `Matrix operator-(const Matrix &other) const`
    - `this - other` の結果を返します。

- `Matrix operator*(const Matrix &other) const`
    - `this * other` の結果を返します。

- `Matrix operator^(long long exponent) const`
    - `this` を `exponent` 乗した結果を返します。

## Complexity

- `N`, `M`, `K`: 行列サイズ
- Addition/Subtraction: `O(NM)`
- Multiplication: `O(NMK)`
- Power: `O(N^3 log X)`

## Code

```cpp
--8<-- "library/math/matrix.hpp"
```
