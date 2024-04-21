#include <bits/stdc++.h>
using namespace std;

/*
Usage:
Calculate primes in the range 1, ... , n
Complexity: O(n ln ln n)
*/
void sieve(vector<bool> &primes, int n){
  primes.assign(n + 1, 1);
  primes[0] = primes[1] = 0;

  for (int i = 2; i * i <= n; i++){
    if (primes[i]){
      for (int j = i * i; j <= n; j+=i){
        primes[j] = false;
      }
    }
  }
}


/*
Example:
*/
int main(){
  int n = 100;
  vector<bool> primes;
  sieve(primes, n);
  for (int i =0 ;i <= n; i++){
    if (primes[i]){
      cout << i << endl;
    }
  }
}