#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class T>
struct StSum {
    vector<T> node;

    void reset(int N) { node.assign(4 * N, 0); }

    void build(const vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = a[vl];  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = node[2 * v] + node[2 * v + 1];  // query op
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = 0;  // neutral element
        if (l >= vr || r <= vl) return val;
        val += query(l, min(r, vm), 2 * v, vl, vm);      // query op
        val += query(max(l, vm), r, 2 * v + 1, vm, vr);  // query op
        return val;
    }

    // set element i to val
    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (i < vm) {
            update(i, val, 2 * v, vl, vm);
        } else {
            update(i, val, 2 * v + 1, vm, vr);
        }
        node[v] = node[2 * v] + node[2 * v + 1];  // query op
    }
};

St<int>

    int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
    }
}
