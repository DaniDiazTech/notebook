// Lazy update segment tree
// Count the number of minimums (Assumes there are no negative values: Count number of zeroes)
struct node{
  int mn, cnt;
  node(){
    mn = 0;
    cnt = 1;
  }
  node (int m, int c){
    mn = m;
    cnt = c;
  }
};



struct segtree{
  vector<node> t;
  vector<int> lazy;
  int N;
  segtree(int n){
    N= n;
    t.assign(4 * n, node());
    lazy.assign(4 * n, 0);
    build(1, 0, N - 1);
  }

  node combine(node a, node b){
    return node(min(a.mn, b.mn), (a.mn == b.mn ? a.cnt + b.cnt : (a.mn < b.mn ? a.cnt : b.cnt)));
  }

  void build(int v, int tl, int tr){
    if (tl == tr){
      return;
    }
    int tm = (tl + tr) / 2;
    build(2 * v, tl, tm);
    build(2 * v + 1, tm + 1, tr);
    t[v] = combine(t[2 * v], t[2 * v + 1]);
  }

  void push(int v){
    t[2 * v].mn += lazy[v];
    t[2 * v + 1].mn += lazy[v];
    lazy[2 * v] += lazy[v];
    lazy[2 * v + 1] += lazy[v];

    lazy[v] = 0;
  }

  void update(int v, int tl, int tr, int l , int r, int val){
    if (l > r) return;
    if (tl == l && tr == r){
      t[v].mn += val;
      lazy[v] += val;
      return; 
    }
    push(v);
    int tm = (tl + tr) / 2;
    update(2 * v, tl, tm, l, min(tm, r), val);
    update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
    t[v] = combine(t[2 * v], t[2 * v + 1]);
  }

  void update(int l, int r, int val){
    update(1, 0, N - 1, l, r, val);
  }

  // mn, cnt in a range
  node query(int v, int tl, int tr, int l, int r){
    if (l > r) return node(inf, 0);
    if (tl == l && tr == r){
      return t[v];
    }
    int tm = (tl + tr) / 2;
    // need to push in order to calculate from children
    push(v);
    return combine( 
      query(2 * v, tl , tm, l, min(r, tm)),
      query(2 * v + 1, tm + 1 , tr, max(l, tm + 1), r)
    );
  }

  node query(int l, int r){
    return query(1, 0, N - 1, l, r);
  }

  // Count zeroes
  int get(int l, int r){
    node temp = query(l, r);
    return (temp.mn == 0 ? temp.cnt : 0);
  }
};
