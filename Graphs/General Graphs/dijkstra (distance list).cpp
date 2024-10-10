// This algorithm returns a list with minimum distances from start to all nodes

// Time complexity: O(|E| log |V|)
// Space complexity: O(|V| + |E|)
// E = edges, V = vertices

// Requires: inf
// Edges should be represented as: pair<node, dist>
template<typename DT>
vector<ll> dijkstra(vector<vector<pair<int, DT>>> &g, int start) {
  const int gn = g.size();
  assert(0 <= start && start < gn);

  vector<ll> tmp(gn, inf);
  vector<ll> dist(gn, inf);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

  tmp[start] = 0;
  pq.push({ tmp[start], start });

  while (!pq.empty()) {
    int node = pq.top().second;
    pq.pop();

    if (dist[node] < inf) continue;
    dist[node] = tmp[node];

    for (auto [adj, w]: g[node]) {
      if (dist[adj] < inf) continue;
      if (tmp[adj] <= dist[node] + w) continue; // If it doesn't improve
      tmp[adj] = dist[node] + w;
      pq.push({ tmp[adj], adj });
    }
  }
  return dist;
  // returns inf if there's no path
}