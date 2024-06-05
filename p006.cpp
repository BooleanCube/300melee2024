#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
#define f first
#define s second
#define sp <<" "<<
#define endl "\n" // remove when debugging

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

    int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

void dfs(int u, int p, vector<vi> &tree, vi &dep) {
    dep[u] = dep[p] + 1;
    for(int v : tree[u]) {
        if(v == p) continue;
        dfs(v, u, tree, dep);
    }
}

int dist(int a, int b, vi &dep, LCA &lca) {
    return dep[a] + dep[b] - 2*dep[lca.lca(a, b)];
}

void solve() {
    int n; cin >> n;
    vector<vi> tree(n);
    rep(i, 0, n-1) {
        int a, b; cin >> a >> b; a--, b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    vi dep(n); dfs(0, 0, tree, dep);
    LCA lca(tree);
    vi perm(n); for(int &x : perm) cin >> x, x--;
    int ans = 1;
    rep(i, 1, n) if(dist(perm[i], perm[i-1], dep, lca) > 3) ans = 0;
    cout << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while(tc--) solve();

    return 0;
}
