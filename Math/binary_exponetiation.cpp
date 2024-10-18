/*
Modular binary exponetiation algorithm:
Returns: (a ^ b) % m

Usage:
binpow(2, 3) = 8
binpow(2, mod - 2) * 2 = 1 (If mod prime)

*/
const int mod = 1e9 + 7;

ll binpow(ll a, ll b){
  if (b == 0) return 1;
  if (b == 1) return a;
  ll x = binpow(a, b / 2);
  return (((x * x) % mod) * (b & 1 ? a : 1ll)) % mod ;
}

/*
Faster iterative implementation
*/
ll binpow(ll a, ll b) {
    a %= mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}