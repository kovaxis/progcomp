#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

struct Node {
    int v, l = 0, r = 0, lzv = 0;
    bool lz = false;
    Node() : v(0) {}
    Node(int x) : v(x) {}
    Node(const Node &a, const Node &b, int l, int r) : v(max(a.v, b.v)), l(l), r(r) {}
    Node(int x, int i, int j, const Node &b) : l(b.l), r(b.r) { v = b.v + x; }
};

// 0 - indexed / inclusive - inclusive
template <class node>
struct PSTL {
    int cnt = 0, n, rc = 0;
    vector<node> st;
    vector<int> rt;

    void push(int u, int v, int i, int j) {
        st[u] = node(v, i, j, st[u]);
        if (i == j) return;
        st[cnt] = st[st[u].l];
        int l = cnt++;
        st[cnt] = st[st[u].r];
        int r = cnt++;
        st[u].l = l, st[l].lz = 1, st[l].lzv += v;
        st[u].r = r, st[r].lz = 1, st[r].lzv += v;
    }
    node query(int u, int a, int b, int i, int j) {
        if (j < a || b < i) return node();
        if (st[u].lz) push(u, st[u].lzv, i, j);
        if (a <= i && j <= b) return st[u];
        int m = (i + j) / 2, l = st[u].l, r = st[u].r;
        return node(query(l, a, b, i, m), query(r, a, b, m + 1, j), l, r);
    }
    int update(int u, int a, int b, int v, int i, int j) {
        if (st[u].lz) push(u, st[u].lzv, i, j);
        if (j < a || b < i) return u;
        st[cnt] = st[u];
        int x = cnt++, m = (i + j) / 2;
        if (a <= i && j <= b) {
            push(x, v, i, j);
            return x;
        }
        int l = st[x].l = update(st[x].l, a, b, v, i, m);
        int r = st[x].r = update(st[x].r, a, b, v, m + 1, j);
        st[x] = node(st[l], st[r], l, r);
        return x;
    }
    int build(vector<node> &arr, int i, int j) {
        int u = cnt++, m = (i + j) / 2;
        if (i == j) {
            st[u] = arr[i];
            return u;
        }
        int l = st[u].l = build(arr, i, m);
        int r = st[u].r = build(arr, m + 1, j);
        st[u] = node(st[l], st[r], l, r);
        return u;
    }

    PSTL() {}
    PSTL(vector<node> &arr) : st(1e7), rt(1e6) {
        n = arr.size();
        rt[rc++] = build(arr, 0, n - 1);
    }
    int update(int t, int a, int b, int v) {
        rt[rc] = update(rt[t], a, b - 1, v, 0, n - 1);
        return rc++;
    }
    node query(int t, int a, int b) { return query(rt[t], a, b - 1, 0, n - 1); }
};

template <class T>
struct Stl3 {
    // immediate, lazy
    vector<pair<T, T>> a;

    T qneutral() { return 0; }
    T merge(T l, T r) { return max(l, r); }
    T uneutral() { return 0; }
    void update(pair<T, T> &u, T val, int l, int r) { u.first += val, u.second += val; }

    Stl3() {}
    Stl3(int N) : a(4 * N, {qneutral(), uneutral()}) {} // node neutral

    void push(int v, int vl, int vm, int vr) {
        update(a[2 * v], a[v].second, vl, vm);     // node update
        update(a[2 * v + 1], a[v].second, vm, vr); // node update
        a[v].second = uneutral();                  // update neutral
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v].first; // query op
        if (l >= vr || r <= vl) return qneutral(); // query neutral
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) update(a[v], val, vl, vr); // node update
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, val, 2 * v, vl, vm);
            update(l, r, val, 2 * v + 1, vm, vr);
            a[v].first = merge(a[2 * v].first, a[2 * v + 1].first); // node merge
        }
    }
};

int N;
vector<pair<int, int>> H;
PSTL<Node> R;
Stl3<int> L;
vector<int> times;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    H.resize(N);
    rep(i, N) cin >> H[i].first;
    rep(i, N) H[i].second = i;

    vector<Node> zeros = vector<Node>(N + 5, Node());
    L = Stl3<int>(N + 5);
    R = PSTL<Node>(zeros);
    sort(H.begin(), H.end(), [](auto &a, auto &b) {
        return a.first > b.first;
    });

    int t = 0;
    for (auto [h, i] : H) {
        int r = R.query(t, i + 1, i + 2).v + 1;
        int l = (i == 0 ? 0 : L.query(i - 1, i)) + 1;
        t = R.update(t, i - l + 1, i + 1, r);
        L.update(i, i + r, l);
        times.push_back(t);
        cerr << "L after adding " << h << ":" << endl;
        rep(i, N) cerr << L.query(i, i + 1) << " ";
        cerr << endl;
        cerr << "R after adding " << h << ":" << endl;
        rep(i, N) cerr << R.query(t, i, i + 1).v << " ";
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

        cerr << endl
             << "checking [" << l << ", " << r << ") with w = " << w << endl;

        int il = 0, ir = N - 1;
        while (il != ir) {
            int t = (il + ir) / 2;
            cerr << "  checking time " << t << endl;
            int tw = R.query(times[t], l, r).v;
            cerr << "  result is " << tw << endl;
            if (tw >= w) ir = t;
            else il = t + 1;
        }

        cout << H[il].first << "\n";
    }
}