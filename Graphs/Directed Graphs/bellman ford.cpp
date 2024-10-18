// This algorithm returns a list with minimum distances from start to all nodes

// Time complexity: O(|V|*|E|)
// Space complexiy: O(|V|)
// V = vertices, E = edges

// Tested: https://cses.fi/problemset/task/1673/
// https://cses.fi/paste/92b468920d420ca8a63b1e/

struct Edge {
  int from, to;
  int weight;
};

// Default graph: 1-indexed directed weighted graph
// Default params:
// edges: List of directed edges of the graph
// gn: number of vertices in the graph
// start: Node from wich the distances begin
/* &reach_neg_cycle: you can pass a variable to save if the graph have at least one negative
  cycle reachable from start */
vector<ll> bellman_ford(vector<Edge> &edges, int gn, int start, bool &neg_cycle) {
  const ll inf = numeric_limits<ll>::max();
  assert(0 < start && start <= gn);

  vector<ll> dist(gn + 1, inf);
  dist[start] = 0;

  // if there is not any negative cycle, it's enough iterate until gn - 1
  for (int i = 0; i < gn; ++i) {
    bool improve = false;
    for (Edge e: edges) {
      if (dist[e.from] == inf) continue;
      if (dist[e.from] + e.weight >= dist[e.to]) continue; // If it doesn't improve
      dist[e.to] = dist[e.from] + e.weight;
      improve = true;
    }
    neg_cycle = improve;
    if (!improve) break;
  }
  return dist;
  // returns numeric_limits<ll>::max() if there's no path
}
