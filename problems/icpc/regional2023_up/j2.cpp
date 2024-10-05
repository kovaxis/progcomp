// https://codeforces.com/gym/104736/problem/J
// upsolved with centroid decomposition

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

int N;
vector<vector<int>> G;
vector<bool> erased;
vector<int> ans;
vector<vector<pair<int, pair<int, int>>>> stk;
vector<vector<pair<int, pair<int, int>>>> stkmin;

int findsize(int u, int p) {
    int sz = 1;
    for (int v : G[u])
        if (v != p && !erased[v]) sz += findsize(v, u);
    return sz;
}

int findcentroid(int u, int p, int n) {
    int sz = 1;
    bool is_cent = true;
    for (int v : G[u])
        if (v != p && !erased[v]) {
            int sub = findcentroid(v, u, n);
            if (sub >= 0) return sub;
            sub = -sub;
            if (sub > n / 2) is_cent = false;
            sz += sub;
        }
    if (n - sz > n / 2) is_cent = false;
    if (is_cent) return u;
    return -sz;
}

void finddepths(int u, int p, int d) {
    stk.back().push_back({u, {d, u}});
    for (int v : G[u])
        if (v != p && !erased[v]) finddepths(v, u, d + 1);
}

void compute(int u) {
    int n = findsize(u, -1);
    u = findcentroid(u, -1, n);
    assert(u >= 0);
    stk.push_back({});
    finddepths(u, -1, 0);
    sort(stk.back().begin(), stk.back().end());
    stkmin.push_back(stk.back());
    invrep(i, stkmin.back().size() - 1) {
        stkmin.back()[i].second = min(stk.back()[i].second, stkmin.back()[i + 1].second);
    }
    pair<int, int> res = {1e9, u};
    rep(k, stk.size()) {
        int extra = lower_bound(stk[k].begin(), stk[k].end(), make_pair(u, make_pair(0, 0)))->second.first;
        auto it = upper_bound(stkmin[k].begin(), stkmin[k].end(), make_pair(u, make_pair(int(1e9), 0)));
        if (it != stkmin[k].end()) {
            pair<int, int> subres = it->second;
            subres.first += extra;
            res = min(res, subres);
        }
    }
    ans[u] = res.second;

    erased[u] = true;
    for (int v : G[u])
        if (!erased[v]) {
            compute(v);
        }

    stk.pop_back();
    stkmin.pop_back();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    G.assign(N, {});
    rep(j, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    erased.assign(N, false);
    ans.resize(N);
    compute(0);

    rep(u, N) cout << ans[u] + 1 << " ";
    cout << endl;
}
