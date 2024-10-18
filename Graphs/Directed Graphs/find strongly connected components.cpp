// let CNT be the number of diferent strongly connected components

// This algorithm assigns each SCC an identifier, these identifiers are
// numbered from 1 to CNT, and finally returns a list of size |V| + 1 with the
// information of wich SCC each node belongs to.
// You can also pass a variable in &cnt to save CNT (number of SCCs)

// Time complexity: O(|V| + |E|)
// Space complexity O(|V|)
// V = vertices, E = edges

// Tested: https://codeforces.com/contest/1900/submission/285409426

// Find strongly connected components
// Default: 1-indexed Directed Unweighted graph not necessarily connected
vector<int> find_SCC(vector<vector<int>> &g, int &cnt) {
  const int inf = 1e9;
  const int gn = (int)g.size() - 1;
 
  vector<bool> in_stack(gn + 1, false);
  vector<bool> vis(gn + 1, false);
  vector<int> who_comp(gn + 1, -1);
  vector<int> tin(gn + 1);
  stack<int> st;
  int timer = 0, tag = 1;
 
  function<int(int)> dfs = [&](int node) -> int {
    vis[node] = true;
    tin[node] = ++timer;
    in_stack[node] = true;
    st.push(node);
    int low = inf;
    for (int adj: g[node]) {
      if (in_stack[adj]) low = min(low, tin[adj]);
      if (vis[adj]) continue;
      low = min(low, dfs(adj));
    }
    if (low == tin[node] || low == inf) {
      while (who_comp[node] == -1) {
        who_comp[st.top()] = tag;
        in_stack[st.top()] = false;
        st.pop();
      }
      ++tag;
      return inf;
    }
    return low;
  };
 
  for (int node = 1; node <= gn; ++node) {
    if (vis[node]) continue;
    dfs(node);
  }
  cnt = tag - 1;
  return who_comp;
}
