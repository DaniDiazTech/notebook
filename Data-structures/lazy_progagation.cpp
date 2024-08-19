// Problem: Add to a range in the array, and query an element
// Build the segment by just assigning the values of the array
// to the leafs, then to update add the value to the nodes corresponding
// to the range given
// To answer the query traverse the tree adding up the values in t

const int mxn= 2e5+ 2;
ll t[mxn * 4];

void build(int v, int l, int r, int a[]){
  if (l == r){
    t[v] = a[l];
    return;
  }
  int m = (l + r) / 2;
  build(2 * v, l, m, a);
  build(2 * v + 1, m + 1, r, a);
}

void update(int v, int tl, int tr, int l, int r, int add){
  if (l > r) return;
  if (tl == l && tr == r){
    t[v] += add;
    return;
  }
  int tm = (tl + tr) / 2;
  update(2 * v, tl, tm, l, min(r, tm), add);
  update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, add);
}

ll query(int v, int tl, int tr, int k){
  if (tl == tr){
    return t[v];
  }

  int tm = (tl + tr) / 2;

  if (k <= tm){
    return t[v] + query(2 * v, tl, tm, k);
  }
  else{
    return t[v] + query(2 * v + 1, tm + 1, tr, k);
  }
}