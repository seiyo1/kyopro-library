#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define de(...) ((void)0)
#define dl(...) ((void)0)
#endif

using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;
using P = pair<ll, ll>;

const ll INF = 1LL << 60;
const int inf = 1073741823;

#define endl '\n'
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rrep(i, m, n) for (int i = (m); i < (n); ++i)
#define per(i, n) for (int i = (n) - 1; i >= 0; --i)
#define fore(x, a) for (auto &x : (a))
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define pb push_back
#define eb emplace_back
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))

template <typename T>
void read_single(T &x) {
  cin >> x;
}

template <typename T, typename... Ts>
void read_single(T &x, Ts &...xs) {
  cin >> x;
  read_single(xs...);
}

#define INT(...)   \
  int __VA_ARGS__; \
  read_single(__VA_ARGS__)
#define LL(...)          \
  long long __VA_ARGS__; \
  read_single(__VA_ARGS__)

template <typename T>
void write_single(const T &x) {
  cout << x;
}

template <typename T>
void write_single(const vector<T> &v) {
  for (size_t i = 0; i < v.size(); ++i) {
    if (i) cout << ' ';
    write_single(v[i]);
  }
}

template <typename T, typename U>
void write_single(const pair<T, U> &p) {
  write_single(p.first);
  cout << ' ';
  write_single(p.second);
}

template <typename T, typename... Ts>
void write_single(const T &x, const Ts &...xs) {
  cout << x;
  if (sizeof...(xs)) {
    cout << ' ';
    write_single(xs...);
  }
}

template <typename T>
void write_single(const vector<vector<T>> &m) {
  for (size_t i = 0; i < m.size(); ++i) {
    write_single(m[i]);
    cout << '\n';
  }
}

#define print(...)             \
  do {                         \
    write_single(__VA_ARGS__); \
    cout << '\n';              \
  } while (0)
#define yesno(cond) PRINT((cond) ? "Yes" : "No")

template <class T>
inline int popcount(T x) {
  return __builtin_popcountll((ull)x);
}

template <class T>
using vec = vector<T>;
template <class T>
using vvec = vector<vector<T>>;

template <class T>
using maxPQ = priority_queue<T>;
template <class T>
using minPQ = priority_queue<T, vector<T>, greater<T>>;

template <class T>
T div_floor(T a, T b) {
  if (b < 0) a = -a, b = -b;
  return a >= 0 ? a / b : (a + 1) / b - 1;
}

template <class T>
T div_ceil(T a, T b) {
  if (b < 0) a = -a, b = -b;
  return a > 0 ? (a - 1) / b + 1 : a / b;
}

template <class T>
inline bool chmin(T &a, const T &b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <typename T, typename U>
T SUM(const vector<U> &A) {
  T sm = 0;
  for (auto &&a : A) sm += a;
  return sm;
}

template <typename T, typename U>
vector<T> cumsum(vector<U> &A, int off = 1) {
  int n = A.size();
  vector<T> B(n + 1);
  rep(i, n) { B[i + 1] = B[i] + A[i]; }
  if (off == 0) B.erase(B.begin());
  return B;
}

template <typename T>
T ipow(T a, long long b) {
  T res = 1;
  while (b > 0) {
    if (b & 1) res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}

// #include <atcoder/all>
// using namespace atcoder;
// using mint=modint998244353;

int main(){
cin.tie(nullptr);
ios_base::sync_with_stdio(false);



return 0;
} 