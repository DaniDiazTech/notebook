// This algorithm modify the residual graph and returns the value of maximum flow

// Time complexity: O(|V| * (|E| ** 2))
// Space complexity: O(|V|)
// V = vertices, E = edges

// tested: https://codeforces.com/group/Ohoz9kAFjS/contest/266572 (Problem B)

ll Edmonds_karp() {
  const int gn = 2 * n;
 
  auto bfs = [&]() -> int {
    int par[gn + 1];
    memset(par, -1, sizeof(par));
    par[source] = -2;
    queue<int> que;
    que.push(source);
 
    while (!que.empty()) {
      int node = que.front();
      que.pop();
 
      if (node == sink) break;
 
      for (int adj: network[node]) {
        if (par[adj] != -1 || cap[node][adj] == 0) continue;
        par[adj] = node;
        que.push(adj);
      }
    }
    if (par[sink] == -1) return 0;
    int cur = sink;
    ll inc_flow = inf;
    while (cur != source) {
      assert(par[cur] > 0);
      inc_flow = min(inc_flow, cap[par[cur]][cur]);
      cur = par[cur];
    }
    cur = sink;
    while (cur != source) {
      cap[par[cur]][cur] -= inc_flow;
      cap[cur][par[cur]] += inc_flow;
      cur = par[cur];
    }
    return inc_flow;
  };
  ll flow, max_flow = 0;
  while (flow = (ll)bfs()) max_flow += flow;
  return max_flow;
}