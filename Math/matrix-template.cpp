#include <bits/stdc++.h>
using namespace std;
long long mod = 1e9 + 7;

/*
Struct matrix, numerical entries.
Usually used with long long or unsigned long long

M rows, N columns matrix
By default 2 * 2 identity matrix.

Addition of matrix O(m * n)
- A(mxn) + B(mxn) = C(mxn)
Multiplication of matrix O(m * n * p):
- A(mxn) * B(nxp) = C(mxp)

Matrix exponentiation O(n^3 * long(b)): Only squared matrices
- A ^ b
*/
template<typename T> struct matrix{
  int M, N;
  vector<vector<T>> A;
  matrix(){}

  matrix(int m, int n, bool iden = false){
    M = m;
    N = n;
    A.assign(M, vector<T>(N, 0));
    if (iden)
      for (int i =0 ;i < min(N, M); i++) A[i][i] = 1;
  }

  matrix(vector<vector<T>> B){
    M = B.size();
    N = B[0].size();
    A=B;
  }

  matrix<T> operator + (matrix<T> B){
    assert("Uncompatible matrix addition" && B.N == N && B.M == M);
    matrix C(M, N);
    for (int i = 0;i < M; i++){
      for (int j = 0;j < N; j++){
        C.A[i][j] = A[i][j] + B.A[i][j];
      }
    }
    return C;
  }
  
  matrix<T> operator * (matrix<T> B){
    assert("Uncompatible matrix multiplication" && N == B.M);
    matrix C(M, B.N);

    for (int i =0;i < M; i++){
      for (int j = 0;j < B.N; j++){
        T sum = 0;
          for (int k = 0; k < N; k++){
          sum += A[i][k] * B.A[k][j];
          sum = ( ((sum) % mod) + mod) % mod;
        }
        C.A[i][j] = sum;
      }
    }
    return C;
  }

  matrix<T> operator ^ (T b){
    matrix<T> C(N, N, true), B(A);
    
    while (b){
      if (b & 1){
        C = C * B;
      }
      B = B * B;
      b /= 2;
    }

    return C;
  }

  void print(){
    for (int i = 0; i < M; i++){
      for (int j =0;j < N; j++){
        cout << A[i][j] << ' ';
      }
      cout << '\n';
    }
  }
};