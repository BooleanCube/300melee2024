#include <bits/stdc++.h>
#include <cmath>
#include <iomanip>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
#define f first
#define s second
#define sp <<" "<<
#define endl "\n" // remove when debugging

void solve() {
    int c, r; cin >> c >> r;
    vi rad(1);
    rep(i, 0, c) {
        int x; cin >> x;
        rad.push_back(x);
    }
    map<int, vi> edges;
    rep(i, 0, r) {
        int a, b; cin >> a >> b;
        edges[a+1].push_back(b);
    }
    int sc, sa, fc, fa; cin >> sc >> sa >> fc >> fa;
    if(sc < fc) { swap(sc, fc); swap(sa, fa); }
    edges[fc].push_back(fa);
    vector<tuple<int, int, ld>> stack; stack.push_back({sc, sa, 0.0});
    ld ans = 1e20;
    while(!stack.empty()) {
        auto [cc, ca, cd] = stack.back(); stack.pop_back();
        if(cd >= ans) continue;
        for(int angle : edges[cc]) {
            int a = min(ca, angle), b = max(ca, angle);
            ld da = min(b - a, 360 + a - b), nd = 2 * M_PI * rad[cc] * (da / 360);
            if(cc == fc && angle == fa) {
                ans = min(ans, cd + nd);
                continue;
            }
            stack.push_back({cc-1, angle, cd+nd+rad[cc]-rad[cc-1]});
        }
    }
    cout << fixed << setprecision(2) << ans << endl;
}

int main() {
    int tc; cin >> tc;
    while(tc--) solve();
    return 0;
}
