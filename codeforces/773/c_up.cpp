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

const int INF = 1e9;

template <class T>
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    Stl() {}
    void resize(int N, T val) { node.resize(4 * N, {val, val}); }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T& lazy = node[v].second;
        node[2 * v].first = lazy;       // update-op & query-op mix
        node[2 * v].second = lazy;      // update-op
        node[2 * v + 1].first = lazy;   // update-op & query-op mix
        node[2 * v + 1].second = lazy;  // update-op
        // lazy = -1;  // update-zero
    }

    // apply the update operation to the range [l, r] (inclusive) in O(log N)
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) {
            node[v].first = val;   // update-op & query-op mix
            node[v].second = val;  // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        if (l <= vm) update(l, min(r, vm), val, 2 * v, vl, vm);
        if (r >= vm + 1) update(max(l, vm + 1), r, val, 2 * v + 1, vm + 1, vr);
        node[v].first =
            max(node[2 * v].first + node[2 * v + 1].first);  // query-op
    }

    // apply the query operation to the range [l, r] (inclusive) in O(log N)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l <= vl && r >= vr) {
            return node[v].first;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        T val = 0;  // query-zero
        if (l <= vm)
            val = max(val, query(l, min(r, vm), 2 * v, vl, vm));  // query-op
        if (r >= vm + 1)
            val = max(val, query(max(l, vm + 1), r, 2 * v + 1, vm + 1,
                                 vr));  // query-op
        return val;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;
    vector<pair<int, pair<int, int>>> qclear;
    vector<pair<int, pair<int, int>>> qsus;
    vector<pair<int, int>> qask;
    Stl<int> notsus;
    Stl<int> time;
    rep(t, Q) {
        int ty;
        cin >> ty;
        if (ty == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            if (x)
                qsus.push_back({t, {l - 1, r - 1}});
            else
                qclear.push_back({t, {l - 1, r - 1}});
        } else {
            int j;
            cin >> j;
            qask.push_back({t, j});
        }
    }
    notsus.resize(N, 0);
    time.resize(N, INF);
    invrep(i, qclear.size()) {
        int t = qclear[i].first;
        int l = qclear[i].second.first;
        int r = qclear[i].second.second;
        notsus.update(l, r, 1);
        time.update(l, r, t);
    }
    for (auto q : qsus) {
        int t = q.first;
        int l = q.second.first;
        int r = q.second.second;
        if (notsus.query()) }
}
