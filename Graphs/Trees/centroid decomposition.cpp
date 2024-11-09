// This algorithm decompose a tree forming a new tree of centroids
// This allows some path computations

// Time complexity in decomposition: O(n * log(n))
// Time complexity by query: O(log(n))
// Space complexity: O(n)

// Tested: https://codeforces.com/gym/104736/submission/290615993
// (https://codeforces.com/gym/104736/problem/J)

class Centroid_decomposition {
  private:
    struct Centroid_info {
      int par = -2;
      int best = // store a case worse than all possible best values, example: INF;
    };
    vector<Centroid_info> info;
    vector<int> siz;
    int initial_node;
  public:
    Centroid_decomposition() {
      siz.clear(); siz.resize(n + 1);
      info.clear(); info.resize(n + 1);
      decompose();
    }
    void dfs_siz(int node, int par) {
      siz[node] = 1;
      for (int child: tree[node]) {
        if (child == par || info[child].par > -2) continue;
        dfs_siz(child, node);
        siz[node] += siz[child];
      }
    }
    int dfs_cen(int node, int par) {
      for (int child: tree[node]) {
        if (child == par || info[child].par > -2) continue;
        if (siz[child] > siz[initial_node] / 2) return dfs_cen(child, node);
      }
      return node;
    }
    int subgraph_centroid(int fnode) {
      initial_node = fnode;
      dfs_siz(fnode, -1);
      return dfs_cen(fnode, -1);
    }
    void decompose() {
      stack<int> centroids;
      int general_centroid = subgraph_centroid(1);
      centroids.push(general_centroid);
      info[general_centroid].par = -1;
      while (!centroids.empty()) {
        int cen = centroids.top();
        centroids.pop();
        for (int adj: tree[cen]) {
          if (info[adj].par > -2) continue;
          int adj_cen = subgraph_centroid(adj);
          info[adj_cen].par = cen;
          centroids.push(adj_cen);
        }
      }
    }
    // Remember to consider the information in paths between
    // the query node and the ancestor centroid
    void update(int node) {
      info[node].best = //...; // store the best answer for this node
      int cur = info[node].par;
      while (cur > -1) {
        info[cur].best = // Try to improve the best answer for ancestor centroids;
        cur = info[cur].par;
      }
    }
    int get(int node) {
      int ans = // store a case worse than all possible best, example: INF;
      int cur = node;
      while (cur > -1) {
        // Compare ans with info[cur].best to improve ans
        cur = info[cur].par;
      }
      return ans;
    }
};
