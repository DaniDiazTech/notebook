/*
Fenwick Tree (BIT)

Range and update queries of a group operation
in O(log n).
*/
template<typename T>
struct BIT{
  vector<T> bit;
  int n;
  BIT(int n){
    bit.assign(n, 0);
    this->n = n;
  }

  BIT (vector<T> &a) : BIT(a.size()){
    for (int i =0 ;i < n ; i++){
      bit[i] += a[i];
      int r = i | (i + 1);
      if (r < n) bit[r] += bit[i];
    }
  }

  // Increments ith element by val
  void update(int i, T val){
    for (; i < n; i = i | (i + 1))
      bit[i] += val;
  }

  // Get A[0, r]
  T query(int r){
    T ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += bit[r];

    return ret;
  }

  // Get A[l, r]
  T query(int l, int r){
    return query(r) - query(l - 1);
  }
};