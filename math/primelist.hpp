//n以下の素数リストを返す
//エラトステネスの篩で O(nlognlogn)
vector<ll> primelist(ll n) {
  vector<ll> primelist;
  vector<bool> isPrime(n + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (ll i = 2; i < n + 1; i++) {
    if (!isPrime[i]) continue;
    for (ll j = i * i; j <= n; j += i) isPrime[j] = false;
  }
  for (ll i = 2; i < n + 1; i++)
    if (isPrime[i]) primelist.push_back(i);
  return primelist;
}