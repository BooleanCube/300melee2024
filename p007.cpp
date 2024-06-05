#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define fre(a) for(auto &u : a)
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
// #define endl "\n" // remove when debugging

int stateToMask(vi &coords) {
    int mask = 0;
    for(int i=7; i>=0; i--) {
        int coord = coords[7-i];
        mask |= (coord << (i*3));
    }
    return mask;
}

void maskToState(int mask, vi &state) {
    for(int i=7; i>=0; i--) {
        state[i] = mask & 7;
        mask >>= 3;
    }
}

void getNextStates(vi &coords, vi &states) {
    vector<vi> mat(6, vi(6, 1));
    int adj[4] = {1, -1, 0, 0};
    auto valid = [](int x, int y, int dx, int dy) { return x+dx>=0 && x+dx<6 && y+dy>=0 && y+dy<6; };
    for(int i=0; i<8; i+=2) mat[coords[i]][coords[i+1]] = 0;
    for(int i=0; i<8; i+=2) {
        int sx = coords[i], sy = coords[i+1];
        for(int j=0; j<4; j++) {
            int x = sx, y = sy, dx = adj[j], dy = adj[3-j];
            while(valid(x, y, dx, dy) && mat[x+dx][y+dy]) x += dx, y += dy;
            if(x == sx && y == sy) continue;
            vi nCoords(8);
            for(int k=0; k<8; k++) nCoords[k] = coords[k];
            nCoords[i] = x, nCoords[i+1] = y;
            states.push_back(stateToMask(nCoords));
        }
    }
}

void getDiff(int a, int b, vi &diff) {
    vi ca(8), cb(8);
    maskToState(a, ca); maskToState(b, cb);
    for(int i=0; i<8; i+=2) {
        if(ca[i] != cb[i] || ca[i+1] != cb[i+1]) {
            diff[0] = ca[i], diff[1] = ca[i+1], diff[2] = cb[i], diff[3] = cb[i+1];
            break;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vi cs(8), ce(8);
    fre(cs) cin >> u; fre(ce) cin >> u;
    int start = stateToMask(cs);
    deque<int> q; q.push_back(start);
    vi vis(1 << 24), par(1 << 24, -1), path(1 << 24);
    path[start] = 1;
    while(!q.empty()) {
        int cur = q.front(); q.pop_front();
        vis[cur] = 1;
        vi coords(8); maskToState(cur, coords);
        vi nbrs; getNextStates(coords, nbrs);
        for(int i=0; i<sz(nbrs); i++) {
            int state = nbrs[i];
            if(vis[state]) continue;
            vis[state] = 1, par[state] = cur, path[state] = path[cur]+1;
            q.push_back(state);
        }
    }
    vi bb;
    vector<pii> es;
    for(int i=0; i<8; i+=2) es.push_back({ce[i], ce[i+1]});
    int mn = INT32_MAX, cur = 0;
    sort(all(es));
    do {
        vi coords(8);
        for(int i=0; i<4; i++) {
            coords[i*2] = es[i].f;
            coords[i*2+1] = es[i].s;
        }
        int cmask = stateToMask(coords);
        if(path[cmask] <= mn) mn = path[cmask], cur = cmask;
    } while(next_permutation(all(es)));
    while(par[cur] > -1) {
        bb.push_back(cur);
        cur = par[cur];
    } bb.push_back(cur);
    cout << sz(bb)-1 << endl;
    for(int i=sz(bb)-1; i>0; i--) {
        vi diff(4);
        getDiff(bb[i], bb[i-1], diff);
        cout << diff[0] sp diff[1] sp diff[2] sp diff[3] << endl;
    }

    return 0;
}
