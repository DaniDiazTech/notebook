#include <bits/stdc++.h>
using namespace std;

/*
DSU data structure:
- Create disjunct sets of nodes, and answer
queries on components of nodes in a graph.

Source: https://cp-algorithms.com/data_structures/disjoint_set_union.html

Complexity:
- Find set: O(lg*n) >= O(1)
- make_set: O(1)
- union_set: O(lg*n) >= O(1)
*/

const int N = 1e6;

int parent[N];
int rank_dsu[N];

// Finds representative of DSU
int find_set(int v) {
  return parent[v] = (v == parent[v] ? v : find_set(parent[v]));
}

void make_set(int v){
  parent[v] = v;
  rank_dsu[v] = 0;
}

void union_set(int u, int  v){
  u = find_set(u);
  v = find_set(v);
  if (u != v){
    // Add tree of lower rank_dsued node to the higher one
    if (rank_dsu[v] > rank_dsu[u])
      swap(u, v); 

    parent[v] = u;
    if (rank_dsu[v] == rank_dsu[u])
      rank_dsu[u]++;
  }
}
