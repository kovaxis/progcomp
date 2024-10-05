#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// handle immutable range maximum queries (or any idempotent query) in O(1)
template <class T>
struct SparseMax {
    vector<vector<T>> st;

    T op(T a, T b) { return max(a, b); }

    SparseMax() {}
    SparseMax(int N) : st{vector<T>(N)} {}

    T &operator[](int i) { return st[0][i]; }

    // O(N log N) time
    // O(N log N) memory
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        repx(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))])); // query op
    }

    // query maximum in the range [l, r) in O(1) time
    // range must be nonempty!
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return op(st[i][l], st[i][r - (1 << i)]); // query op
    }
};
template <class T>
struct SparseMin {
    vector<vector<T>> st;

    T op(T a, T b) { return min(a, b); }

    SparseMin() {}
    SparseMin(int N) : st{vector<T>(N)} {}

    T &operator[](int i) { return st[0][i]; }

    // O(N log N) time
    // O(N log N) memory
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        repx(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))])); // query op
    }

    // query maximum in the range [l, r) in O(1) time
    // range must be nonempty!
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return op(st[i][l], st[i][r - (1 << i)]); // query op
    }
};

template <class T>
struct StSum {
    int n;
    vector<T> a;

    T neut() { return 0; }
    T merge(T x, T y) { return x + y; }

    StSum(int n = 0) : n(n), a(2 * n, neut()) {}

    T query(int l, int r) {
        T x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, T x) {
        for (a[i += n] = x; i /= 2;) a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};

int N;
vector<int> A;
SparseMax<int> mx;
SparseMin<int> mn;
StSum<ll> sm;

bool can_merge(int l, int r, ll x) {
    l = max(l, 0);
    r = min(r, N);
    if (l >= r) return false;
    if (mn.query(l, r) == mx.query(l, r)) {
        return mn.query(l, r) > x;
    }
    return sm.query(l, r) > x;
}

int solve(int i) {
    int l = 1, r = N + 1;
    while (l != r) {
        int m = (l + r) / 2;
        if (can_merge(i - m, i, A[i]) || can_merge(i + 1, i + m + 1, A[i])) r = m;
        else l = m + 1;
    }
    if (l == N + 1) return -1;
    else return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];

        mx = {N};
        rep(i, N) mx[i] = A[i];
        mx.init();

        mn = {N};
        rep(i, N) mn[i] = A[i];
        mn.init();

        sm = {N};
        rep(i, N) sm.update(i, A[i]);

        rep(i, N) cout << solve(i) << " ";
        cout << "\n";
    }
}
