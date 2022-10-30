#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

// x, y
vector<pair<ll, ll>> b;

ll evalcost(ll x) {
    ll cost = INF;
    for (pair<ll, ll> p : b) cost = min(cost, p.second + abs(p.first - x));
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        int N, P;
        cin >> N >> P;
        vector<vector<ll>> a(N, vector<ll>(P));
        rep(i, N) rep(j, P) cin >> a[i][j];

        b.clear();
        vector<pair<ll, ll>> c(N, {INF, -INF});
        rep(i, N) for (ll x : a[i]) c[i].first = min(c[i].first, x),
                                    c[i].second = max(c[i].second, x);

        b.push_back({0, 0});
        rep(i, N) {
            auto [l, r] = c[i];
            // go right, then left
            ll lcost = evalcost(r) + r - l;
            // go left, then right
            ll rcost = evalcost(l) + r - l;

            // cerr << "client " << i << endl;
            // cerr << "  cost to go to " << l << " then " << r << ": " << rcost
            //     << endl;
            // cerr << "  cost to go to " << r << " then " << l << ": " << lcost
            //     << endl;

            b.clear();
            b.push_back({l, lcost});
            b.push_back({r, rcost});
        }
        ll ans = INF;
        for (pair<ll, ll> p : b) ans = min(ans, p.second);
        cout << "Case #" << tc + 1 << ": " << ans << "\n";
    }
}
