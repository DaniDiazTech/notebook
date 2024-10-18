// This algorithm returns a list of bridges in a graph
// The format of these bridges is an edge list where each edge
// is a pair<int, int> and satisfies (edge.first < edge.second)

// Time complexity: O(|V| + |E|)
// Space complexity: O(|V| + |E|)
// V = vertices, E = edges

// Tested: https://codeforces.com/contest/1986/submission/286603550

// Default param: (0/1)-indexed undirected unweighted graph not necessarily connected
vector<pair<int, int>> get_bridges(vector<vector<int>> &g) {
  const int inf = 1e9;
  const int gn = (int)g.size();
  vector<pair<int, int>> bridges;
  vector<bool> vis(gn, false);
  vector<int> tim(gn);

  function<int(int, int)> dfs = [&](int node, int par) -> int {
    vis[node] = true;
    int low = inf;
    for (int adj: g[node]) {
      if (adj == par) continue;
      if (vis[adj]) low = min(low, tim[adj]);
      if (vis[adj]) continue;
      tim[adj] = tim[node] + 1;
      int nxt_low = dfs(adj, node);
      if (nxt_low == inf) bridges.emplace_back(min(node, adj), max(node, adj));
      low = min(low, nxt_low);
    }
    if (low == tim[node]) return inf;
    return low;
  };
  for (int node = 0; node < gn; ++node) {
    if(vis[node]) continue;
    dfs(node, -1);
  }
  return bridges;
}
