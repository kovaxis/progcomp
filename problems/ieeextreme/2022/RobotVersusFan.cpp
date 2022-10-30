#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int R, D;
char M[512][512];

int seent[512][512];
vector<pair<int, int>> r_move, d_move;
int r_cycle;

ll mod(ll x, ll M) {
    return (x % M + M) % M;
}

ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

pair<ll, ll> solve_crt(pair<ll, ll> eq0, pair<ll, ll> eq1) {
    ll a0 = eq0.first, p0 = eq0.second;

    ll a1 = eq1.first, p1 = eq1.second;
    ll k1, k0;
    ll d = ext_gcd(p1, p0, k1, k0);
    a0 -= a1;
    if (a0 % d != 0) return {-1, -1};
    p0 = p0 / d * p1;
    a0 = a0 / d * k1 % p0 * p1 % p0 + a1;
    a0 = (a0 % p0 + p0) % p0;

    return {a0, p0};
}

ll solve() {
    rep(t, r_cycle) {
        auto d_pos = d_move[t % d_move.size()];
        if (r_move[t] == d_pos) return t;
    }
    ll mint = 1e18;
    repx(tt, r_cycle, r_move.size()) {
        ll rm = r_move.size() - r_cycle;
        ll rt = tt % rm;

        ll dm = D;
        ll dt = tt % D;

        auto [ft, fm] = solve_crt({rt, rm}, {dt, dm});
        if (fm == -1) continue;

        ft += r_cycle / fm * fm;
        while (ft - fm >= r_cycle) ft -= fm;

        mint = min(mint, ft);
    }
    if (mint == 1e18) return -1;
    return mint;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> R;
        rep(i, R) rep(j, R) cin >> M[i][j];
        cin >> D;
        rep(t, D) {
            int i, j;
            cin >> i >> j;
            d_move[t] = {i, j};
        }

        rep(i, R) rep(j, R) seent[i][j] = -1;
        r_move.clear();
        for (int i = 0, j = 0, t = 0;; t++) {
            if (seent[i][j] != -1) {
                r_cycle = seent[i][j];
            }
            r_move.push_back({i, j});
            if (M[i][j] == '>') j += 1;
            if (M[i][j] == '<') j -= 1;
            if (M[i][j] == '^') i -= 1;
            if (M[i][j] == 'v') i += 1;
        }

        ll ans = solve();
        if (ans == -1) {
            cout << "never\n";
        } else {
            cout << ans << "\n";
        }
    }
}
