#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll INF = 1e18;

inline ll ceildiv(ll a, ll b) {
    ll d = a / b;
    return d * b == a ? d : d - ((a < 0) ^ (b < 0)) + 1;
}

template <class T>
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    Stl() {}
    void reset(int N) { node.assign(4 * N, {0, 0}); }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T& lazy = node[v].second;
        node[2 * v].first += lazy;       // update-op & query-op mix
        node[2 * v].second += lazy;      // update-op
        node[2 * v + 1].first += lazy;   // update-op & query-op mix
        node[2 * v + 1].second += lazy;  // update-op
        lazy = 0;                        // update-zero
    }

    // apply the update operation to the range [l, r] (inclusive) in O(log N)
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) {
            node[v].first += val;   // update-op & query-op mix
            node[v].second += val;  // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        if (l <= vm) update(l, min(r, vm), val, 2 * v, vl, vm);
        if (r >= vm + 1) update(max(l, vm + 1), r, val, 2 * v + 1, vm + 1, vr);
        node[v].first =
            min(node[2 * v].first, node[2 * v + 1].first);  // query-op
    }

    // apply the query operation to the range [l, r] (inclusive) in O(log N)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l <= vl && r >= vr) {
            return node[v].first;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        T val = INF;  // query-zero
        if (l <= vm)
            val = min(val, query(l, min(r, vm), 2 * v, vl, vm));  // query-op
        if (r >= vm + 1)
            val = min(val, query(max(l, vm + 1), r, 2 * v + 1, vm + 1,
                                 vr));  // query-op
        return val;
    }
};

int N, M, Mtotal, L;
vector<int> rawt;
vector<vector<int>> rawg;
vector<ll> gsums;
Stl<ll> avail;
string ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        rawt.resize(N);
        rawg.resize(M);
        rep(i, N) cin >> rawt[i];
        rep(i, M) {
            int K;
            cin >> K;
            rawg[i].resize(K);
            rep(j, K) cin >> rawg[i][j];
        }

        Mtotal = 0;
        rep(i, M) Mtotal += rawg[i].size();
        ans.assign(Mtotal, '?');

        L = 0;
        rep(i, N) L = max(L, rawt[i]);
        rep(i, M) for (int x : rawg[i]) L = max(L, x);
        avail.reset(L + 1);

        gsums.assign(M, 0);
        rep(i, M) for (int x : rawg[i]) gsums[i] += x;

        rep(i, N) avail.update(0, rawt[i], 1);
        rep(i, M) {
            ll avg = ceildiv(gsums[i], rawg[i].size());
            avail.update(0, avg, -1);
        }

        int idx = 0;
        rep(i, M) {
            int K = rawg[i].size();
            rep(j, K) {
                ll oldavg = ceildiv(gsums[i], K);
                ll newavg = ceildiv(gsums[i] - rawg[i][j], K - 1);
                avail.update(0, oldavg, 1);
                avail.update(0, newavg, -1);
                bool ok = avail.query(0, L) >= 0;
                ans[idx++] = '0' + ok;
                avail.update(0, newavg, 1);
                avail.update(0, oldavg, -1);
            }
        }

        cout << ans << "\n";
    }
}
