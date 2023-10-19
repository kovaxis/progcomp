#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

template <class T>
struct Stl {
    int n;
    vector<T> a, b;

    T qneut() { return -2e9; }
    T uneut() { return 0; }
    T merge(T x, T y) { return max(x, y); }
    void upd(int v, T x, int l, int r) { a[v] += x, b[v] += x; }

    Stl(int n = 0) : n(n), a(4 * n, qneut()), b(4 * n, uneut()) {}

    void push(int v, int vl, int vm, int vr) {
        upd(2 * v, b[v], vl, vm);
        upd(2 * v + 1, b[v], vm, vr);
        b[v] = uneut();
    }

    // compute the query operation for the range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l <= vl && r >= vr) return a[v];
        if (l >= vr || r <= vl) return qneut();
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr));
    }

    // apply update operation to range [l, r)
    void update(int l, int r, T x, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) upd(v, x, vl, vr);
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, x, 2 * v, vl, vm);
            update(l, r, x, 2 * v + 1, vm, vr);
            a[v] = merge(a[2 * v], a[2 * v + 1]);
        }
    }

    void set(int i, T x) {
        T y = query(i, i + 1);
        update(i, i + 1, x - y);
    }
};

/*
template <class T>
struct Stl {
    // immediate, lazy
    vector<pair<T, T>> a;

    T qneutral() { return -2e9; }
    T merge(T l, T r) { return max(l, r); }
    T uneutral() { return 0; }
    void update(pair<T, T> &u, T val, int l, int r) { u.first += val, u.second += val; }

    Stl() {}
    Stl(int N) : a(4 * N, {qneutral(), uneutral()}) {} // node neutral

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

    void set(int i, T x) {
        T y = query(i, i + 1);
        update(i, i + 1, x - y);
    }
};*/

int N, K;
// position -> height
vector<int> P;
// height -> position
vector<int> R;
// height -> dp value
vector<Stl<int>> dp;

#define cerr \
    if (0) cerr

int solve() {
    cerr << "H:";
    rep(i, N) cerr << " " << P[i];
    cerr << endl;

    R.resize(N);
    rep(i, N) R[i] = i;
    sort(R.begin(), R.end(), [](int i, int j) {
        if (P[i] != P[j]) return P[i] < P[j];
        return i > j;
    });
    rep(i, N) P[R[i]] = i;

    cerr << "R:";
    rep(i, N) cerr << " " << R[i];
    cerr << endl;

    cerr << "P:";
    rep(i, N) cerr << " " << P[i];
    cerr << endl;

    dp.resize(K + 1, {N});
    rep(i, N) {
        int h = P[i];
        repx(k, 1, K + 1) {
            dp[k].update(h + 1, N, 1);
            if (k == 1) {
                if (i == 0) dp[k].set(h, 1);
            } else {
                dp[k].set(h, dp[k - 1].query(0, h) + 1);
            }
            cerr << "dp[" << i + 1 << "][" << k << "] (h = " << h << ") = " << dp[k].query(h, h + 1) << endl;
        }
    }

    int mx = dp[K].query(0, N);
    if (mx < 0) return -1;
    return N - mx;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int L;
    cin >> N >> L >> K;
    L--;
    P.resize(N);
    rep(i, N) cin >> P[i];

    int base = 0;
    rep(i, L) if (P[i] >= P[L]) base += 1;
    P.erase(P.begin(), P.begin() + L);
    N -= L;

    int ans = solve();
    if (ans != -1) ans += base;
    cout << ans << endl;
}