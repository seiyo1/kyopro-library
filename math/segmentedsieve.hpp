 //(sqrtR）までのふるい
  auto primes = primelist(int(1e7 + 9));
  //[L,R]を区間ふるい
  vector<bool> isPrime(R - L + 1, true);
  for (ll p : primes) {
    ll start = max(((L + p) / p) * p, (ll)p * p);
    for (ll i = start; i <= R; i += p) {
      if (!isPrime[i - L]) continue;
      isPrime[i - L] = false;
    }
  }