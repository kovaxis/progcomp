#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

template <class T>
struct Node {
    T x, lz;
    int l = -1, r = -1;
};

template <class T>
struct Pstl {
    int N;
    vector<Node<T>> a;
    vector<int> head;

    T qneut() { return 0; }
    T merge(T l, T r) { return max(l, r); }
    T uneut() { return 0; }
    T accum(T u, T x) { return u + x; }
    T apply(T x, T lz, int l, int r) { return x + lz; }

    int build(int vl, int vr) {
        if (vr - vl == 1) a.push_back({qneut(), uneut()}); // node construction
        else {
            int vm = (vl + vr) / 2, l = build(vl, vm), r = build(vm, vr);
            a.push_back({merge(a[l].x, a[r].x), uneut(), l, r}); // query merge
        }
        return a.size() - 1;
    }

    T query(int l, int r, int v, int vl, int vr, T acc) {
        if (l >= vr || r <= vl) return qneut();                    // query neutral
        if (l <= vl && r >= vr) return apply(a[v].x, acc, vl, vr); // update op
        acc = accum(acc, a[v].lz);                                 // update merge
        int vm = (vl + vr) / 2;
        return merge(query(l, r, a[v].l, vl, vm, acc), query(l, r, a[v].r, vm, vr, acc)); // query merge
    }

    int update(int l, int r, T x, int v, int vl, int vr) {
        if (l >= vr || r <= vl || r <= l) return v;
        a.push_back(a[v]);
        v = a.size() - 1;
        if (l <= vl && r >= vr) {
            a[v].x = apply(a[v].x, x, vl, vr); // update op
            a[v].lz = accum(a[v].lz, x);       // update merge
        } else {
            int vm = (vl + vr) / 2;
            a[v].l = update(l, r, x, a[v].l, vl, vm);
            a[v].r = update(l, r, x, a[v].r, vm, vr);
            a[v].x = merge(a[a[v].l].x, a[a[v].r].x); // query merge
        }
        return v;
    }

    Pstl() {}
    Pstl(int N) : N(N) { head.push_back(build(0, N)); }

    T query(int t, int l, int r) {
        return query(l, r, head[t], 0, N, uneut()); // update neutral
    }
    int update(int t, int l, int r, T x) {
        return head.push_back(update(l, r, x, head[t], 0, N)), head.size() - 1;
    }
};

int N;
vector<pair<int, int>> H;
Pstl<int> L, R;
vector<int> times;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    H.resize(N);
    rep(i, N) cin >> H[i].first;
    rep(i, N) H[i].second = i;

    L = {N + 1};
    R = {N + 1};
    sort(H.begin(), H.end(), [](auto &a, auto &b) {
        return a.first > b.first;
    });

    int t = 0;
    for (auto [h, i] : H) {
        int r = R.query(t, i + 1, i + 2) + 1;
        int l = (i == 0 ? 0 : L.query(t, i - 1, i)) + 1;
        R.update(t, i - l + 1, i + 1, r);
        t = L.update(t, i, i + r, l);
        times.push_back(t);

        cerr << "L after adding " << h << ":" << endl;
        rep(i, N) cerr << L.query(t, i, i + 1) << " ";
        cerr << endl;
        cerr << "R after adding " << h << ":" << endl;
        rep(i, N) cerr << R.query(t, i, i + 1) << " ";
        cerr << endl
             << endl;
    }

    int Q;
    cin >> Q;
    rep(q, Q) {
        int l, r, w;
        cin >> l >> r >> w;
        l--;
        r -= w - 1;

        if (l == 0) cerr << endl
                         << "checking [" << l << ", " << r << ") with w = " << w << endl;

        int il = 0, ir = N - 1;
        while (il != ir) {
            int t = (il + ir) / 2;
            int tw = R.query(times[t], l, r);
            if (l == 0) {
                cerr << "  checking time " << t << endl;
                cerr << "  result is  " << tw << endl;
                cerr << "  R values at this time:" << endl;
                rep(i, N) cerr << R.query(t, i, i + 1) << " ";
                cerr << "  R values by 2 at this time:" << endl;
                rep(i, N - 1) cerr << R.query(t, i, i + 2) << " ";
                cerr << endl;
            }
            if (tw >= w) ir = t;
            else il = t + 1;
        }

        cout << H[il].first << "\n";
    }
}