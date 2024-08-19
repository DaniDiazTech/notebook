// Segment tree nodes indexed in 1
// Array is indexed in 0
// Query: [l, r]
// Update: [l, r]
template<typename T> 
struct segtree{
  vector<T> t;
  const T NEUTRAL = 0;

  // Size of array
  int N = 0;
  segtree(int n){
    N = n;
    t.assign(4 * N, NEUTRAL);
  }
  segtree(vector<T> &a){
    N = a.size();
    t.assign(4 * N, NEUTRAL);

    build(1, 0, N - 1, a);
  }

  T combine(T a, T b){
    // combine two elements into one
    return a + b;
  }

  void build(int v, int l, int r, vector<T> &a){
    if (l == r){
      t[v] = a[l];
    }
    else{
      int m = (l + r) /2 ;
      build(2 * v, l, m, a); 
      build(2 * v + 1, m + 1, r, a); 
      t[v] = combine(t[2 * v], t[2 * v + 1]);
    }
  }

  T get(int l, int r){
    return query(1, 0, N - 1, l, r);
  }

  T query(int v, int tl, int tr, int l, int r){
    if (l > r){
      return NEUTRAL;
    }
    if (tl == l && tr == r){
      return t[v];
    }

    int tm = (tl + tr) / 2;
    return combine(
      query(2 * v, tl, tm, l, min(tm, r)),
      query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r)
    );
  }

  void put(int pos, int val){
    update(1, 0, N - 1, pos, val);
  }

  void update(int v, int tl, int tr, int pos, int val){
    if (tl == tr){
      t[v] = val;
      return;
    }
    int tm = (tl + tr) / 2;
    if (tl <= pos && pos <= tm){
      update(2 * v, tl, tm, pos, val);
    }
    else{
      update(2 * v + 1, tm + 1, tr, pos, val);
    }
    t[v] = combine(t[2 * v], t[2 * v + 1]);
  }

};