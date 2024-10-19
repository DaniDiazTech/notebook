// Find value of maximum flow
// Let F be the value of maximum flow
// Time complexity: O(F * (|V| + |E|))
// Space complexity: O(|V|)

vector<vector<int>> network(n + 1);
vector<bool> vis(n + 1);
int cap[mxN + 1][mxN + 1];
memset(cap, 0, sizeof(cap));

int dfs(int node, int min_cap) {
  vis[node] = true;
  if (node == sink) return min_cap;
 
  for (int adj: network[node]) {
    if (vis[adj]) continue;
    int next = cap[node][adj];
    if (!next) continue;
    int flow = dfs(adj, min(min_cap, next));
    cap[node][adj] -= flow;
    cap[adj][node] += flow;
    if (flow) return flow;
  }
  return 0;
}
// Find maximum flow
int max_flow = 0;
int flow = 0;
while (flow = dfs(source, inf)) {
  max_flow += flow;
  fill(vis.begin(), vis.end(), false);
}