
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

int N, root;
vector<vector<int>> G;
vector<int> nxt;

struct R {
    mutable ll S, N;
    mutable int u, v;

    bool operator<(R r) const {
        // n / d < r.n / r.d
        return S * r.N < r.S * N;
    }

    bool operator<=(R r) const {
        return !(r < *this);
    }

    bool operator==(R r) const {
        return S * r.N == r.S * N;
    }

    void append(R r) const {
        S += r.S;
        N += r.N;
        nxt[v] = r.u;
        v = r.v;
    }
};

set<R> dfs(int u, int p) {
    set<R> res;
    for (int v : G[u])
        if (v != p) {
            set<R> sub = dfs(v, u);
            if (sub.size() > res.size()) swap(sub, res);
            for (R newf : sub) {
                auto oldf = res.find(newf);
                if (oldf == res.end()) {
                    res.insert(newf);
                } else {
                    oldf->append(newf);
                }
            }
        }
    R me = R{u + 1, 1, u, u};
    while (res.size() && *res.begin() <= me) {
        R sub = *res.begin();
        res.erase(res.begin());
        me.append(sub);
    }
    res.insert(me);
    // cerr << "order for u = " << u + 1 << endl;
    // for (R f : res) {
    //     cerr << "  group " << f.S << "/" << f.N << " " << f.u << ":";
    //     for (int u = f.u; u != -1; u = nxt[u]) {
    //         cerr << " " << u + 1;
    //     }
    //     cerr << endl;
    // }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> root;
    root--;
    G.assign(N, {});
    rep(j, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    nxt.assign(N, -1);
    set<R> order = dfs(root, -1);

    ll n = 1, ans = 0;
    for (R f : order) {
        for (int u = f.u; u != -1; u = nxt[u]) {
            ans += n * (u + 1);
            n += 1;
        }
    }

    cout << ans << endl;
}
