#include <bits/stdc++.h>
using namespace std;

/*
Calculates phi or the euler totient function
for a number i. (# coprimes in 1 ... n)

n = mult ( pi ^ ei)
phi(n) = n * mult (1 - pi)

We have the equation:
n (1 - p) = n - (n / p)
Thus we can easily calculate the value of phi

Complexity: O(sqrt(n))
Trial division:
It is enough to iterate through all primes that divide n
in 1 ... sqrt(n).
The algorithm skips composite numbers, thus only operating with primes that divide n.
*/

int phi(int n){
  int res = n;
  for (int i = 2; i * i <= n; i++){
    if (n % i){
      while (n % i){
        n /= i;
      }
      res -= res / i;
    }
  }
  // n prime
  if (n > 1){
    res -= res / n;
  }

  return res;
}

/*
Compute phi from 1 to n
Use the sieve concept to only iterate through prime multiples
and modify the answer for each value
Complexity: O(n ln ln n)
*/

void phi_1_to_n(vector<int> &phi, int n){
  phi.resize(n + 1);
  for (int i = 0;i <= n; i++) phi[i] = i;

  for (int i = 2; i * i <= n; i++){
    for (int j = i; j <= n; j+=i){
      phi[j] -= phi[j] / i;
    }
  }
}