#include <bits/stdc++.h>
using namespace std;

/*
Usage:
Calculate primes in the range 1, ... , n
Complexity: O(n ln ln n)
*/
void run_sieve(vector<bool> &sieve, int n){
  sieve.assign(n + 1, 1);
  sieve[0] = sieve[1] = 0;

  for (long long i = 2; i * i <= n; i++){
    if (sieve[i]){
      for (long long j = i * i; j <= n; j+=i){
        sieve[j] = false;
      }
    }
  }
}

/*
Create primes up to a number N.
Complexity: O(n ln ln n)
*/

void gen_primes(vector<bool> &sieve, vector<int> &primes, int n){
  sieve.assign(n + 1, 1);
  primes.clear();
  sieve[0] = sieve[1] = 0;

  for (long long i = 2; i <= n; i++){
    if (sieve[i]){
      primes.push_back((int)i);
      for (long long j = i * i; j <= n; j+=i){
        sieve[j] = false;
      }
    }
  }

}


/*
Example:
*/
int main(){
  int n = 100;
  vector<bool> sieve;
  run_sieve(sieve, n);
  for (int i =0 ;i <= n; i++){
    if (sieve[i]){
      cout << i << endl;
    }
  }

  int m = 1000000;
  vector<int> primes;
  gen_primes(sieve, primes, m);  
  cout << primes.size() << '\n';
  // for (auto p: primes){
  //   cout << p << '\n';
  // }
}