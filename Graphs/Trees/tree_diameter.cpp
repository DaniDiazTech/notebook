// The diameter of a tree is the length of the longest path
// between any two nodes.
// In this algorithm the length of a path is considered as
// the number of edges in the path.

// This algorith returns the value of the diameter

// Time complexity: O(|V|)
// Space complexity: O(1)
// V = Vertices

// Tested: https://codeforces.com/gym/102694/submission/286468111 (Problem A)

// Default param: 1-indexed unweighted Tree with at least 1 node
int tree_diameter(vector<vector<int>> &tree) {
  int diameter = 0;
  function<int(int, int)> dfs = [&](int node, int par) -> int {
    int mx = 0, smx = 0;
    for (int child: tree[node]) {
      if (child == par) continue;
      int chdep = dfs(child, node);
      if (chdep > mx) smx = mx, mx = chdep;
      else if (chdep > smx) smx = chdep;
    }
    diameter = max(diameter, smx + mx);
    return mx + 1;
  };
  dfs(1, -1);
  return diameter;
}
