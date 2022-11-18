#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class T>
struct St3 {
    vector<T> node;

    T neutral() { return 1e18; }
    T merge(T l, T r) { return min(l, r); }

    void reset(int N) { node.assign(4 * N, neutral()); } // node neutral

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v]; // item construction
        int vm = (vl + vr) / 2;
        if (l >= vr || r <= vl) return neutral();                                 // item neutral
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // set element i to val
    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) node[v] = val; // item update
        else {
            int vm = (vl + vr) / 2;
            if (i < vm) update(i, val, 2 * v, vl, vm);
            else update(i, val, 2 * v + 1, vm, vr);
            node[v] = merge(node[2 * v], node[2 * v + 1]); // node merge
        }
    }
};

int N;
vector<ll> a;
St3<ll> c;

int findr(int ql) {
    int l = ql, r = N;
    while (l != r) {
        int m = (l + r + 1) / 2;
        if (c.query(ql, m) + ql > 0) l = m;
        else r = m - 1;
    }
    return r;
}

ll solve() {
    c.reset(N);
    rep(i, N) c.update(i, a[i] - i);

    ll ans = 0;
    rep(l, N) {
        int r = findr(l);
        ans += r - l;
        // cerr << "array [" << l + 1 << ", " << r << "] is valid" << endl;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        cout << solve() << "\n";
    }
}
