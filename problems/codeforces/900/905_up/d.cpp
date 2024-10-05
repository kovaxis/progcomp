#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const int INF = 1e9;

struct Res {
    int mn, mx;
    vector<pair<int, int>> splits;

    friend ostream &operator<<(ostream &s, Res r) {
        s << r.mn << " " << r.mx << " (";
        for (auto [l, r] : r.splits) s << " [" << l << ", " << r - 1 << "]";
        s << " )";
        return s;
    }
};

struct Ans {
    int mn, mx, split;

    friend ostream &operator<<(ostream &s, Ans r) {
        s << r.mn << " " << r.mx << " (";
        if (r.split != INF) s << " " << r.split;
        s << " )";
        return s;
    }
};

int N, Q;
vector<int> A, L, R;
vector<Res> st;

void build(int v, int vl, int vr) {
    if (vl >= vr) return;
    if (vr - vl == 1) {
        st[v] = {A[vl], A[vl], {}};
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v, vl, vm);
    build(2 * v + 1, vm, vr);

    Res &l = st[2 * v], &r = st[2 * v + 1];
    assert(l.mn <= l.mx && r.mn <= r.mx);
    int mn = min(l.mn, r.mn), mx = max(l.mx, r.mx);
    vector<pair<int, int>> splits;
    for (auto [xl, xr] : l.splits) {
        if (xl < r.mn) splits.push_back({xl, min(xr, r.mn)});
    }
    if (l.mx < r.mn) splits.push_back({l.mx, r.mn});
    for (auto [xl, xr] : r.splits) {
        if (xr > l.mx) splits.push_back({max(xl, l.mx), xr});
    }
    st[v] = {mn, mx, splits};

    cerr << "[" << vl + 1 << ", " << vr << "] " << st[v] << endl;
}

void query(int l, int r, Ans &res, int v, int vl, int vr) {
    if (l >= r || l >= vr || r <= vl) return;
    if (l <= vl && r >= vr) {
        Res &x = st[v];
        assert(x.mn <= x.mx);
        if (res.mn > res.mx) {
            // res is empty
            if (x.splits.size()) res.split = x.splits[0].first;
        } else if (res.split < x.mn) {
            // the current split is ok
        } else if (res.mx < x.mn) {
            // split just at the border
            res.split = res.mx;
        } else {
            // try splitting x
            res.split = INF;
            auto it = upper_bound(x.splits.begin(), x.splits.end(), res.mx, [](int x, pair<int, int> s) {
                return x < s.second;
            });
            if (it != x.splits.end()) {
                res.split = max(res.mx, it->first);
            }
        }
        res.mn = min(res.mn, x.mn);
        res.mx = max(res.mx, x.mx);

        cerr << "query [" << l + 1 << ", " << vr << "] " << res << endl;
    } else {
        int vm = (vl + vr) / 2;
        query(l, r, res, 2 * v, vl, vm);
        query(l, r, res, 2 * v + 1, vm, vr);
    }
}

bool query(int l, int r) {
    Ans res = {INF, -INF, INF};
    query(l, r, res, 1, 0, N);
    return res.split != INF;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];
    cin >> Q;
    L.resize(Q), R.resize(Q);
    rep(q, Q) cin >> L[q] >> R[q];
    rep(q, Q) L[q] -= 1;

    st.resize(4 * N, {INF, -INF, {}});
    build(1, 0, N);

    rep(q, Q) {
        cout << (query(L[q], R[q]) ? "Yes" : "No") << "\n";
    }
}
