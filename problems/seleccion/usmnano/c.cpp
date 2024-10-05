#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Edge {
    int u, v;
    ll w;
};

int N, M, Qn;
vector<vector<Edge>> G;
vector<pair<int, int>> Q;

vector<ll> B;
vector<bool> seen;

ll basis[64];
bool has[64];

bool add(ll a) {
    invrep(i, 60) {
        if ((a >> i) & 1) {
            if (has[i]) {
                a ^= basis[i];
            } else {
                basis[i] = a;
                has[i] = true;
                return true;
            }
        }
    }
    return false;
}

void dfs(int u) {
    seen[u] = true;
    for (Edge e : G[u]) {
        if (seen[e.v]) {
            ll cyc = B[u] ^ B[e.v] ^ e.w;
            add(cyc);
        } else {
            B[e.v] = B[u] ^ e.w;
            dfs(e.v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Qn;
    G.resize(N);
    rep(j, M) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].push_back({u, v, w});
        G[v].push_back({v, u, w});
    }
    Q.resize(Qn);
    rep(qi, Qn) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        Q[qi] = {u, v};
    }

    seen.assign(N, false);
    B.assign(N, 0);
    dfs(0);

    for (auto [u, v] : Q) {
        ll d = B[u] ^ B[v];
        invrep(i, 60) {
            if (((d >> i) & 1) && has[i]) {
                d ^= basis[i];
            }
        }
        cout << d << "\n";
    }
}
