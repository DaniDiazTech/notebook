// This algorithm returns the cardinality of maximum bipartite matching

// Time complexity: O(sqrt(|V|) * |E|)
// Space complexity O(|V|)
// V = vertices, E = edges

// Tested: https://codeforces.com/gym/101853/submission/288023394

const int inf = 1e9;

// Requires inf
class Bip_Graph {
  int m, n;
  list<int> *adj;
  int *pairU, *pairV, *dist;
  int neutral = 0;
 
  public:
    Bip_Graph(int m, int n);
    void addEdge(int u, int v);
 
    bool bfs();
    bool dfs(int u);
    int hopcroftKarp();
};
 
int Bip_Graph::hopcroftKarp() {
  pairU = new int[m + 1];
  pairV = new int[n + 1];
  dist = new int[m + 1];
 
  for (int u = 0; u <= m; ++u) pairU[u] = neutral;
  for (int v = 0; v <= n; ++v) pairV[v] = neutral;
 
  int result = 0;
 
  while (bfs()) {
    for (int u = 1; u <= m; ++u) {
      if (pairU[u] == neutral && dfs(u)) {
        ++result;
      }
    }
  }
  return result;
}
 
bool Bip_Graph::bfs() {
  queue<int> que;
 
  for (int u = 1; u <= m; ++u) {
    if (pairU[u] == neutral) {
      dist[u] = 0;
      que.push(u);
    }
    else dist[u] = inf;
  }
  dist[neutral] = inf;
 
  while (!que.empty()) {
    int u = que.front();
    que.pop();
 
    if (dist[u] < dist[neutral]) {
      list<int>::iterator i;
      for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (dist[pairV[v]] == inf) {
          dist[pairV[v]] = dist[u] + 1;
          que.push(pairV[v]);
        }
      }
    }
  }
  return (dist[neutral] != inf);
}
 
bool Bip_Graph::dfs(int u) {
  if (u != neutral) {
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
      int v = *i;
      if (dist[pairV[v]] == dist[u] + 1) {
        if (dfs(pairV[v]) == true) {
          pairV[v] = u;
          pairU[u] = v;
          return true;
        }
      }
    }
    dist[u] = inf;
    return false;
  }
  return true;
}
 
Bip_Graph::Bip_Graph(int m, int n) {
  this -> m = m;
  this -> n = n;
  adj = new list<int>[m + 1];
}
void Bip_Graph::addEdge(int u, int v) {
  adj[u].push_back(v);
}

// Example of use
BipGraph g(4, 4);
g.addEdge(1, 2);
g.addEdge(1, 3);
g.addEdge(2, 1);
g.addEdge(3, 2);
g.addEdge(4, 2);
g.addEdge(4, 4);

cout << "Size of maximum matching is " << g.hopcroftKarp();
