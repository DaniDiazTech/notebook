/*
problem: https://codeforces.com/problemset/problem/1082/G
submission: https://codeforces.com/contest/1082/submission/286264949
*/
#include<bits/stdc++.h>
#define all(a) a.begin(),a.end()
#define forn(u,n) for(int u=0;u<n;++u)
#define sz(a) ((int)a.size())
#define pb push_back

using namespace std;

typedef long long ll;

const unsigned long long  MOD = 1000567999;
int n,m;
struct edge { int v, cap, inv, flow; };
struct Dinic{ // O(n^2 * m)
	int n, src, dst;
	vector<int> dist, q, work; // dist: distancias desde S, sin ponderar
	struct edge {int to, rev; ll f, cap;};
	vector<vector<edge>> g; vector<ll> dd;
	Dinic(int n_): n(n_), dist(n_+2), q(n_+2), work(n_+2), g(n_+2), dd(n_+2)
	               {} // Deja espacio para el min_cap
	void add_edge(int s, int t, ll cap, ll mincap = 0){
		// assert(0 <= mincap and mincap <= cap);
		dd[s] += mincap; dd[t] -= mincap;
		g[s].pb({t, sz(g[t]),   0, cap-mincap});
		g[t].pb({s, sz(g[s])-1, 0, 0}); // Residual: cap = 0 y flujo < 0
	}
	bool dinic_bfs(){
		fill(all(dist), -1); dist[src] = 0;
		int qt = 0; q[qt++] = src;
		for(int qh = 0; qh < qt; qh ++){
			int u = q[qh];
			for(auto e: g[u]){
				int v = e.to;
				if(dist[v] < 0 and e.f < e.cap) dist[v] = dist[u]+1, q[qt++] = v;
			}
		}
		return dist[dst] >= 0;
	}
	ll dinic_dfs(int u, ll f){
		if(u == dst) return f;
		for(int &i = work[u]; i < sz(g[u]); i ++){
			edge &e = g[u][i];
			if(e.cap <= e.f) continue;
			int v = e.to;
			if(dist[v] == dist[u]+1){
				ll df = dinic_dfs(v, min(f, e.cap - e.f));
				if(df > 0){
					e.f += df; g[v][e.rev].f -= df;
					return df;
				}
			}
		}
		return 0;
	}
	ll max_flow(int _src, int _dst){
		src = _src; dst = _dst;
		ll result = 0;
		while(dinic_bfs()){
			fill(all(work), 0);
			while(ll delta = dinic_dfs(src, INT_MAX)) result += delta;
		}
		return result;
	}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>n>>m;
    Dinic network(n+m+2);
    int s=0, t= n+m+1;
    forn(i,n){
        int x;
        cin>>x;
        network.add_edge(i+1,t,x);
    }
    ll tot=0;
    forn(i,m){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        tot+=w;
        network.add_edge(s,n+i+1,w);
        network.add_edge(n+i+1,u,INT_MAX);
        network.add_edge(n+i+1,v,INT_MAX);
    }
    cout<<tot-network.max_flow(s,t)<<"\n";
}
