/*
 The goal is to maximize the number of such edges, ensuring that no node is matched more than once. The maximum flow in this network corresponds to the size of the maximum matching.
/// Complexity: O(|E|*|V|)
Tested: https://vjudge.net/solution/54826125/1o9jH7bQJk9BOsHl6rbq
*/
struct mbm {
  vector<vector<int>> g;
  vector<int> d, match;
  int nil, l, r;
  /// u -> 0 to l, v -> 0 to r
  mbm(int l, int r) : l(l), r(r), nil(l+r), g(l+r),
                      d(1+l+r, INF), match(l+r, l+r) {}
  map<int, int> L, R;
  void add_edge(int a, int b) {//Adds edges to the graph
    if(!L.count(a)) { int t = L.size(); L[a] = t; }
    if(!R.count(b)) { int t = R.size(); R[b] = t; }
    a = L[a];
    b = R[b];
    g[a].push_back(l+b);
    g[l+b].push_back(a);
  }
  bool bfs() {
    queue<int> q;
    for(int u = 0; u < l; u++) {
      if(match[u] == nil) {
        d[u] = 0;
        q.push(u);
      } else d[u] = INF;
    }
    d[nil] = INF;
    while(q.size()) {
      int u = q.front(); q.pop();
      if(u == nil) continue;
      for(auto v : g[u]) {
        if(d[ match[v] ] == INF) {
          d[ match[v] ] = d[u]+1;
          q.push(match[v]);
        }
      }
    }
    return d[nil] != INF;
  }
  bool dfs(int u) {
    if(u == nil) return true;
    for(int v : g[u]) {
      if(d[ match[v] ] == d[u]+1 && dfs(match[v])) {
        match[v] = u; match[u] = v;
        return true;
      }
    }
    d[u] = INF;
    return false;
  }
  int max_matching() {//finds the maximum bipartite matching
    int ans = 0;
    while(bfs()) {
      for(int u = 0; u < l; u++) {
        ans += (match[u] == nil && dfs(u));
      }
    }
    return ans;
  }
};
