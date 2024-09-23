/*
Answer offlines queries based on an ordering that guarantees
O((n + q)sqrt(n))

Set block = sqrt(n)
Uses global variables and other data structures if needed.
*/
int block;
struct Query{
  int l, r, ind;

  bool operator < (Query other) const{
    return make_pair(l / block, r)  < make_pair(other.l/block, other.r);    
  }
};

// Add and remove objects according to the problem
void add(int i){
}

void remove(int i){
}

int get_ans(){
}


void mo(vector<Query> &queries){
  sort(queries.begin(), queries.end());
  vector<ll> ans(queries.size());
  
  int cur_l = queries[0].l, cur_r = queries[0].l - 1;
  for (Query q: queries){
    // Make cur_l = q.l and cur_r = q.r
    while (cur_l < q.l) remove(cur_l++);
    while (cur_l > q.l) add(--cur_l);

    while(cur_r > q.r) remove(cur_r--);
    while (cur_r < q.r) add(++cur_r);

    ans[q.ind] = get_ans();
  }

  // Print answer
  for (auto x: ans) cout << x << "\n";
}
