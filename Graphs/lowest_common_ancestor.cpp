/*
Lowest common ancestor

Gets the lca of two nodes of a rooted tree in O(log n).

dfs(): Traverses the tree and calculates node ancestors in powers
of two.

Calculates other helper arrays:

- par: Parent of nodes
- tin, tout: DFS in and out times
- height: Height of each node starting at 0 (root)

Tested: https://codeforces.com/contest/1328/submission/284525277
*/
int n, l;

vector<int> tin, tout, par, height;
vector<vector<int>> g, up;

int timer = 0;

void dfs(int u, int p){


  par[u] = p;
  height[u] = (u == p ? 0 : height[p] + 1);

  tin[u] = timer++;
  
  up[u][0] = p;

  for (int i = 1;i <= l; i++){
    up[u][i] = up[up[u][i - 1]][i - 1];
  }

  for (auto v: g[u]){
    if (v == p) continue;

    dfs(v, u);
  }

  tout[u] = timer++;
}

bool is_ancestor(int u, int v){
  return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v){
  if (is_ancestor(u, v)) return u;
  if (is_ancestor(v, u)) return v;
  
  for (int i = l; i >= 0; i--){
    if (!is_ancestor(up[u][i], v)) u = up[u][i];
  }

  return up[u][0];
}

void preprocess(int root){
  // G processed
  timer = 0;
  l = ceil(log2(n));

  tin.resize(n + 1);
  tout.resize(n + 1);
  par.resize(n + 1);
  height.resize(n + 1);
  up.assign(n + 1, vector<int>(l + 1));


  dfs(root, root);
}
