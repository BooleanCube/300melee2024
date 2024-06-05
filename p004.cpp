#include <bits/stdc++.h>
using namespace std;

#define int ll
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
#define f first
#define s second
#define sp <<" "<<
#define endl "\n" // remove when debugging

int area(pii a, pii b, pii c) {
    int area = (a.f*b.s - b.f*a.s) + (b.f*c.s - c.f*b.s) + (c.f*a.s - a.f*c.s);
    return abs(area) << 1;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<pii> pts(n);
    for(auto &u : pts) cin >> u.f >> u.s;
    pii door = pts[0];
    int ta = 0;
    rep(i, 1, n-1) ta += area(door, pts[i], pts[i+1]);
    int target = ta >> 1, cur = 0;
    rep(i, 1, n-1) {
        int ct = area(door, pts[i], pts[i+1]);
        if(cur + ct  >= target) {
            ld m = (ld)(target-cur)/(ld)(ct);
            ld px = (pts[i+1].f - pts[i].f) * m, py = (pts[i+1].s - pts[i].s) * m;
            cout << fixed << setprecision(8) << (pts[i].f + px) sp (pts[i].s + py) << endl;
            return 0;
        }
        cur += ct;
    }
    // should never get here
    cout << "0 0" << endl;

    return 0;
}
