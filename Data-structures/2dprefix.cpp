
/*
2d prefix sum.

Calculates the sum of a submatrix in O(1)
with O(N * M) precalc.
*/

template<typename T>
struct prefix2d{
  int N, M;
  vector<vector<T>> p;

  prefix2d(vector<vector<T>> &a){
    N = a.size();
    M = a[0].size();

    // resize
    p.assign(N, vector<T>(M));

    for (int i = 0; i < N; i++){
      for (int j = 0; j < M; j++){
        p[i][j] = a[i][j];
        p[i][j] += (i > 0 ? p[i - 1][j]: 0); 
        p[i][j] += (j > 0 ? p[i][j - 1] : 0);
        p[i][j] -= (i > 0 && j > 0 ? p[i - 1][j - 1] : 0);
      }
    }

  }

  // 0-indexed 
  T query(int x1, int x2, int y1, int y2){
    T ret = p[x2][y2];

    ret -= (x1 > 0 ? p[x1 - 1][y2] : 0) ;
    ret -= (y1 > 0 ? p[x2][y1 - 1] : 0) ;
    ret += (x1 > 0 && y1 > 0 ? p[x1 - 1][y1 - 1] : 0) ;

    return ret;
  }


  void print(){
    for (int i =0 ;i < N; i++){
      for (int j =0 ;j < M; j++){
        cout << p[i][j] << ' ';
      }
      cout << endl;
    }
  }

};
