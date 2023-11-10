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

        floyd();

        int mu = 0, mv = 0;
        rep(u, N) rep(v, N) {
            if (D[u][v] >= D[mu][mv]) mu = u, mv = v;
        }
        ll d1 = D[mu][mv] - 1;

        if (K == 1) {
            cout << d1 << endl;
            continue;
        }

        // cerr << "giving away on " << mv + 1 << " to " << mu + 1 << endl;
        ll og = C[mv][mu];
        C[mv][mu] = -d1;

        floyd();

        int mmu = 0, mmv = 0;
        rep(u, N) rep(v, N) {
            if (D[u][v] >= D[mmu][mmv] && (u != mu || v != mv)) {
                mmu = u, mmv = v;
                // cerr << "current max: " << mmu + 1 << " to " << mmv + 1 << endl;
            }
        }
        ll d2 = D[mmu][mmv] - 1;
        // cerr << "2nd giving away on " << mmv + 1 << " to " << mmu + 1 << endl;

        ll sol = d1 + d2;

        vector<pair<int, int>> forbid;

        // try 2
        rep(tr, 4) {
            forbid.push_back({mu, mv});
            C[mv][mu] = og;

            mu = 0, mv = 0;
            rep(u, N) rep(v, N) {
                bool skip = false;
                for (auto [fu, fv] : forbid)
                    if (u == fu && v == fv) skip = true;
                if (skip) continue;
                if (D[u][v] >= D[mu][mv]) mu = u, mv = v;
            }
            d1 = D[mu][mv] - 1;

            // cerr << "giving away on " << mv + 1 << " to " << mu + 1 << endl;
            og = C[mv][mu];
            C[mv][mu] = -d1;

            floyd();

            mmu = 0, mmv = 0;
            rep(u, N) rep(v, N) {
                if (D[u][v] >= D[mmu][mmv] && (u != mu || v != mv)) {
                    mmu = u, mmv = v;
                    // cerr << "current max: " << mmu + 1 << " to " << mmv + 1 << endl;
                }
            }
            d2 = D[mmu][mmv] - 1;
            // cerr << "2nd giving away on " << mmv + 1 << " to " << mmu + 1 << endl;

            sol = max(sol, d1 + d2);
        }

        cout << sol << endl;
    }
}
