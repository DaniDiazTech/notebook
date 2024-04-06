#include <bits/stdc++.h>
using namespace std;

/*
Hamiltonian path:

Let G be a graph with n vertices.
A hamiltonian path is a simple path (No repeating vertices) with length n.

This is an NP complete problem.
Complexity: O(2^n * n^2)

Idea: Let a single path of G ending at v. To extend this single path
we don't care about the order of the previous vertices, thus
we can use a subset, and the ending to v to solve the problem.

In: Adjacency matrix, number of nodes
Out: Exists hamiltonian path

Tested: https://codeforces.com/contest/1950/submission/255328975
*/

bool is_hamiltonian(vector<vector<int>> &adj, int n){
  // Ending node, subset
  bool dp[n][1 << n];
  memset(dp, 0, sizeof dp);
  
  for (int i = 0; i < n; i++){
    dp[i][1 << i] = 1;
  }

  for (int mask = 0; mask < (1 << n); mask++){
    for (int u = 0; u < n; u++){
      if (mask & (1 << u)){
        for (int v = 0; v < n; v++){
          // Can create a single path from v to u
          // Iff there is a single path ending at v not including u
          if (mask & (1 << v) && v != u && adj[u][v] && dp[v][mask ^ (1 << u)]){
            dp[u][mask] = 1;
          }
        }
      }
    } 
  }

  for (int i = 0;i < n; i++){
    // Complete subsets for every ending node
    if (dp[i][(1 << n) - 1]){
      return true;
    }
  }

  return false;
}


int main(){
  /*
  4 3
  0 1
  1 2
  1 3 
  */
	int n, m; cin >> n >> m;
	vector<vector<int>> adj(n, vector<int>(n));
	for (int i =0 ;i < m; i++){
		int u, v; cin >> u >> v;
    // Undirected
		adj[u][v] = adj[v][u] = 1;
	}

	bool f = is_hamiltonian(adj, n);
	cout << (f ? "YES": "NO") << '\n';
}
