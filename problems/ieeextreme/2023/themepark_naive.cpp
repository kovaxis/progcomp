#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

int N, K;
ll C[500][500], D[500][500];
map<string, int> mapping;

int conv(string name) {
    if (mapping.count(name)) return mapping[name];
    else return mapping[name] = mapping.size();
}

void floyd() {
    rep(u, N) rep(v, N) D[u][v] = C[u][v];
    rep(k, N) rep(u, N) rep(v, N) {
        D[u][v] = min(D[u][v], D[u][k] + D[k][v]);
    }
}

pair<ll, ll> solve_limited(ll mx) {

    int m2u = 0, m2v = 0;
    rep(u, N) rep(v, N) {
        if (D[u][v] >= D[m2u][m2v] && D[u][v] <= mx) m2u = u, m2v = v;
    }
    ll d1 = D[m2u][m2v] - 1;
    if (K == 1) return {D[m2u][m2v], d1};

    // cerr << "giving away on " << mv + 1 << " to " << mu + 1 << endl;
    ll og = C[m2v][m2u];
    C[m2v][m2u] = -d1;

    floyd();

    int mmu = 0, mmv = 0;
    rep(u, N) rep(v, N) {
        if (D[u][v] >= D[mmu][mmv] && (u != m2u || v != m2v && D[u][v] <= mx)) {
            mmu = u, mmv = v;
            // cerr << "current max: " << mmu + 1 << " to " << mmv + 1 << endl;
        }
    }
    ll d2 = D[mmu][mmv] - 1;

    C[m2v][m2u] = og;
    return {D[m2u][m2v], d1 + d2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        mapping.clear();
        string a, b;
        rep(i, N) {
            rep(j, N) if (i != j) {
                ll w;
                cin >> a >> b >> w;
                int u = conv(a), v = conv(b);
                C[u][v] = w;
            }
        }

        auto [mx, sol] = solve_limited(1e9);
        if (K == 1) return sol;

        ll max_sol = sol;
        invrep(mx2, mx) {
            auto [new_mx, this_sol] = solve_limited(mx2);
            if (this_sol > max_sol) {
                cerr << "found better solution!" << endl;
                max_sol = this_sol;
            }
        }

        cout << max_sol << endl;
    }
}
