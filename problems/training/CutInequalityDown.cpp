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

struct Dsu {
    vector<int> p, r;

    Dsu() {}
    // initialize the disjoint-set-union to all unitary sets
    void reset(int N) {
        p.resize(N), r.assign(N, 0);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two sets with leaders `i` and `j`
    // note: `i` and `j` must be GROUP LEADERS
    void unite(int i, int j) {
        if (i == j) return;
        if (r[i] > r[j]) swap(i, j);
        if (r[i] == r[j]) r[j] += 1;
        p[i] = j;
    }
};

struct Query {
    int t, id;
    ll x;
};

ll N, L, U, Q;
vector<ll> a;
vector<Query> evs;
int nxt_q;
// real + offset = in-memory
// real = in-memory - offset
ll offset;
Dsu groups;
vector<ll> ans;
vector<ll> invb;
map<ll, int> b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> L >> U;
    a.resize(N + 1);
    rep(i, N) cin >> a[i];
    cin >> Q;
    rep(i, Q) {
        int b, e;
        ll x;
        cin >> b >> e >> x;
        evs.push_back({b - 1, i, x});
        evs.push_back({e - 1 + 1, i, -1});
    }

    sort(evs.begin(), evs.end(), [](Query& l, Query& r) { return l.t < r.t; });
    groups.reset(Q);
    invb.resize(Q);
    ans.resize(Q);

    rep(t, N + 1) {
        while (nxt_q < evs.size() && evs[nxt_q].t <= t) {
            auto& q = evs[nxt_q];
            nxt_q += 1;

            if (q.x >= 0) {
                ll x = q.x + offset;
                int id = q.id;
                if (b.count(x)) {
                    groups.unite(groups.find(b[x]), id);
                    id = groups.find(id);
                }
                b[x] = id;
                invb[id] = x;
                // cerr << "added scenario " << q.id + 1 << " into x = " << x
                //     << " (real = " << x + offset << " with offset = " <<
                //     offset
                //     << ")" << endl;
            } else {
                ll x = invb[groups.find(q.id)];
                // cerr << "answering for query " << q.id + 1 << ", x = " << x
                //     << " (real = " << x - offset << ")" << endl;
                ans[q.id] = x - offset;
            }
        }

        offset -= a[t];
        // cerr << "new offset is " << offset << endl;

        {
            int u_id = -1;
            for (auto it = b.lower_bound(U + offset); it != b.end();
                 it = b.erase(it)) {
                if (u_id == -1) u_id = it->second;
                groups.unite(groups.find(u_id), groups.find(it->second));
            }
            if (u_id != -1) {
                u_id = groups.find(u_id);
                b[U + offset] = u_id;
                invb[u_id] = U + offset;
            }
        }

        {
            int l_id = -1;
            auto end_it = b.lower_bound(L + offset + 1);
            for (auto it = b.begin(); it != end_it; it = b.erase(it)) {
                if (l_id == -1) l_id = it->second;
                groups.unite(groups.find(l_id), groups.find(it->second));
            }
            if (l_id != -1) {
                l_id = groups.find(l_id);
                b[L + offset] = l_id;
                invb[l_id] = L + offset;
            }
        }
    }

    for (ll x : ans) {
        cout << x << "\n";
    }
}
