#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

ll binexp(ll a, ll e, ll M = MOD) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a % M;
        a = a * a % M;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M = MOD) { return binexp(a, M - 2, M); }

int N;
vector<int> A;
vector<vector<int>> iG;

vector<bool> seen, mark;
int fw(int u) {
    if (seen[u]) {
        return u;
    }
    seen[u] = true;
    return fw(A[u]);
}

vector<int> comp;
void bk(int u) {
    if (mark[u]) return;
    mark[u] = true;
    comp.push_back(u);
    for (int v : iG[u]) bk(v);
}

vector<int> cycle, iscycle;
void cyc(int u) {
    cycle.clear();
    cycle.push_back(u);
    iscycle[u] = true;
    u = A[u];
    while (u != cycle[0]) {
        cycle.push_back(u);
        iscycle[u] = true;
        u = A[u];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];
    rep(i, N) A[i]--;

    iG.resize(N);
    rep(i, N) iG[A[i]].push_back(i);

    seen.resize(N, false), mark.resize(N, false), iscycle.resize(N, false);

    ll ans = 1;
    rep(u, N) {
        if (mark[u]) continue;
        int v = fw(u);
        comp.clear();
        bk(v);
        cyc(v);

        ll res = 1;
        for (int v : cycle) {
            res = res * ll(iG[v].size() + 1) % MOD;
        }
        for (int v : cycle) {
            res = (MOD + res - ll(iG[v].size())) % MOD;
        }
        for (int v : comp)
            if (!iscycle[v]) {
                res = res * ll(iG[v].size() + 1) % MOD;
            }
        ans = ans * res % MOD;
    }

    cout << ans << endl;
}
