vector<vector<int>> tree;

const int LOG = 20; /// max N < 2^LOG
const int mxN = 2e5; /// max N
int up[mxN + 1][LOG];
// You can declare more vectors with additional info of tree here
// Example: int maximum_edge[mxN + 1][LOG];
int dep[mxN + 1];
int root = 1;

void build_lca(int node, int par) {
  for (int i = 1; i < LOG; ++i) {
    if (up[node][i - 1] == -1) break;
    up[node][i] = up[up[node][i - 1]][i - 1];
    // You must calculate jumps in vectors with additional info here
    // Example: maximum_edge[node][i] = max(maximum_edge[node][i - 1], maximum_edge[up[node][i - 1]][i - 1]);
  }
  for (int child: tree[node]) {
    if (child == par) continue;
    dep[child] = dep[node] + 1;
    up[child][0] = node;
    // You must set child data in vectors with additional info here
    // Example: maximum_edge[child][0] = edge_weight;
    build_lca(child, node);
  }
}

void init_lca() {
  memset(up, -1, sizeof(up));
  memset(dep, -1, sizeof(dep));
  // You must set initial content of vectors with additional info here
  // Example: memset(maximum_edge, -1, sizeof(maximum_edge));
  build_lca(root, -1);
}

int lca(int a, int b) {
  if (dep[a] < dep[b]) swap(a, b);
  int dif = dep[a] - dep[b];
  for (int k = 0; k < LOG; ++k) {
    if (dif & (1 << k)) a = up[a][k];
  }
  if (a == b) return a;
  for (int k = LOG - 1; 0 <= k; --k) {
    if (up[a][k] == up[b][k]) continue;
    a = up[a][k];
    b = up[b][k];
  }
  return up[a][0];
}
