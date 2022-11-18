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

    T neutral() { return 0; }
    T merge(T l, T r) { return l + r; }

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
ll S;
vector<int> a, d, pr, ig;
St3<ll> unlock, block;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) cin >> a[i];

    d.resize(N);
    rep(i, N) d[i] = i - a[i];

    {
        int r = 0;
        pr.resize(N);
        rep(l, N) {
            while (r < N && d[r] < l) r += 1;
            pr[l] = r;
        }
    }

    {
        int r = 0;
        ig.resize(N);
        rep(i, N) {
            r = min(max(r, pr[i] + 1), N);
            while (r < N && d[r] < i) r += 1;
            ig[i] = r;
        }
    }

    unlock.reset(N);
    rep(i, N) unlock.update(i, ig[i] - pr[i]);

    block.reset(N);
    rep(i, N) block.update(i, pr[i]);

    S = 0;
    rep(l, N) S += pr[l] - l;

    // cerr << "d:";
    // rep(i, N) cerr << " " << d[i];
    // cerr << endl;
    // cerr << "pr:";
    // rep(i, N) cerr << " " << pr[i];
    // cerr << endl;
    // cerr << "ig:";
    // rep(i, N) cerr << " " << ig[i];
    // cerr << endl;

    int Q;
    cin >> Q;
    rep(q, Q) {
        int i, x;
        cin >> i >> x;
        i -= 1;

        int nd = i - x;
        ll s = S;
        if (nd == d[i]) {
        } else if (nd < d[i]) {
            // unlock contribution that was blocked on this value and is above nd
            int lo = lower_bound(pr.begin(), pr.end(), i) - pr.begin();
            int hi = upper_bound(pr.begin(), pr.end(), i) - pr.begin();
            lo = max(lo, nd + 1);
            s += unlock.query(lo, hi);
        } else if (nd > d[i]) {
            // block contribution that was not blocked before and is at or below nd
            int lo = upper_bound(pr.begin(), pr.end(), i) - pr.begin();
            int hi = i + 1;
            hi = min(hi, nd + 1);
            if (lo < hi) s -= block.query(lo, hi) - (ll)(hi - lo) * i;
        }

        cout << s << "\n";
    }
}
