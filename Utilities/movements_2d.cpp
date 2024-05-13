/*
Used for movements in a 2d matrix. Useful for Graph problems on graphs.
Tested: https://codeforces.com/gym/518941/submission/257482117
*/
// L R U D LU LD RU RD
int dr[] = {0, 0, -1, 1, -1, 1, -1, 1};
int dc[] = {-1, 1, 0, 0, -1, -1, 1, 1};

// N rows, M columns
int n, m;
bool valid(int i, int j){
  return i >= 0 && j >= 0 && i < n && j < m;
}