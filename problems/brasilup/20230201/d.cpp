#pragma GCC optimize("O2")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

template <class T>
struct Node {
    T s, c;
    int l = -1, r = -1;

    Node() : s(0), c(0) {}
    Node(T x) : s(x), c(1) {}
    Node(Node a, Node b, int l = -1, int r = -1) : s(a.s + b.s), c(a.c + b.c), l(l), r(r) {}
};

// UNTESTED
template <class T>
struct Pst {
    int N;
    vector<T> a;
    vector<int> head;

    int build(int vl, int vr) {
        if (vr - vl == 1) a.push_back(T()); // node construction
        else {
            int vm = (vl + vr) / 2, l = build(vl, vm), r = build(vm, vr);
            a.push_back(T(a[l], a[r], l, r)); // query merge
        }
        return a.size() - 1;
    }

    T query(int l, int r, int v, int vl, int vr) {
        if (l >= vr || r <= vl) return T(); // query neutral
        if (l <= vl && r >= vr) return a[v];
        int vm = (vl + vr) / 2;
        return T(query(l, r, a[v].l, vl, vm), query(l, r, a[v].r, vm, vr)); // query merge
    }

    int update(int i, T x, int v, int vl, int vr) {
        a.push_back(a[v]);
        v = a.size() - 1;
        if (vr - vl == 1) a[v] = x; // update op
        else {
            int vm = (vl + vr) / 2;
            if (i < vm) a[v].l = update(i, x, a[v].l, vl, vm);
            else a[v].r = update(i, x, a[v].r, vm, vr);
            a[v] = T(a[a[v].l], a[a[v].r], a[v].l, a[v].r); // query merge
        }
        return v;
    }

    Pst() {}
    Pst(int N) : N(N) { head.push_back(build(0, N)); }

    T query(int t, int l, int r) {
        return query(l, r, head[t], 0, N);
    }
    int update(int t, int i, T x) {
        return head.push_back(update(i, x, head[t], 0, N)), head.size() - 1;
    }
};

int N;
vector<pair<ll, int>> H;
Pst<Node<ll>> Zt;

pair<ll, int> count_points(int l, int r, int at, int bt) {
    auto az = Zt.query(at, l, r);
    auto bz = Zt.query(bt, l, r);
    ll sm = bz.s - az.s;
    ll cnt = bz.c - az.c;
    return {sm, cnt};
}

// returns true if count in range is zero
bool is_average_over(int l, int r, int at, int bt, ll avg) {
    auto [sm, cnt] = count_points(l, r, at, bt);
    // sm / cnt >= avg ?
    return sm >= cnt * avg;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    H.resize(N);
    rep(i, N) cin >> H[i].first;
    rep(i, N) H[i].second = i;

    Zt = {N};
    sort(H.begin(), H.end());
    for (auto [h, i] : H) {
        Zt.update(Zt.head.size() - 1, i, h);
    }

    int Q;
    cin >> Q;
    rep(q, Q) {
        ll L, R, Ah, Bh, avg;
        cin >> L >> R >> Ah >> Bh >> avg;
        L--;

        int At = lower_bound(H.begin(), H.end(), make_pair(Ah, 0)) - H.begin();
        int Bt = upper_bound(H.begin(), H.end(), make_pair(Bh, N)) - H.begin();

        int lo = At, hi = Bt;
        while (lo != hi) {
            int m = (lo + hi) / 2;
            if (is_average_over(L, R, m, Bt, avg)) hi = m;
            else lo = m + 1;
        }

        cout << count_points(L, R, lo, Bt).second << "\n";
    }
    // cerr << "maxc = "<<MAXC<<endl;
    // cerr << "maxr = "<<MAXR<<endl;
}