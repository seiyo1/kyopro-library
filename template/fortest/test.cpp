#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
  #include "/home/yz/comp/debug.hpp"
#else
  #define de(...) ((void)0)
  #define dl(...) ((void)0)
#endif

using  ll  = long long;
using  ull = unsigned long long;
using  i128 = __int128_t;
using  P = pair<ll,ll>;

const ll  INF = 1LL << 60;
const int inf = 1073741823;

#define endl   '\n'
#define rep(i,n)     for(int i = 0; i < (n); ++i)
#define rrep(i,m,n)  for(int i = (m); i < (n); ++i)
#define per(i,n)     for(int i = (n) - 1; i >= 0; --i)
#define fore(x,a)    for(auto &x : (a))
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define pb  push_back
#define eb  emplace_back

template<class T>
inline int popcount(T x){ return __builtin_popcountll((ull)x); }

template<class T> using vec   = vector<T>;
template<class T> using vvec  = vector<vector<T>>;

template<class T> using maxPQ = priority_queue<T>;
template<class T> using minPQ = priority_queue<T, vector<T>, greater<T>>;

template<class T>
inline bool chmin(T &a, const T &b){ if(a > b){ a = b; return true; } return false; }

template<class T>
inline bool chmax(T &a, const T &b){ if(a < b){ a = b; return true; } return false; }

template<typename T>
T ipow(T a, long long b){
    T res = 1;
    while(b > 0){
        if(b & 1) res *= a;  
        a *= a;              
        b >>= 1;
    }
    return res;
}

// #include <atcoder/all>
// using namespace atcoder;
// using mint=modint998244353;
//compile->test run->t
int main(){
cin.tie(nullptr);
ios_base::sync_with_stdio(false);
int n;cin>>n;
if(n==100)cout<<1<<endl;
else cout<<n<<endl;





return 0;
}