// 5F

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

// handle immutable range maximum queries (or any idempotent query) in O(1)
template <class T>
struct Sparse {
    vector<vector<T>> st;

    T op(T a, T b) { return max(a, b); }

    Sparse() {}
    Sparse(int N) : st{vector<T>(N)} {}

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

int N;
vector<ll> A, B;
Sparse<ll> As, Bs;

// find the max winnable carrot in a K-size range
ll solvemax(ll K) {
    ll margin = (K - 1) / 2;
    if (K % 2) {
        return As.query(margin, N - margin);
    } else {
        return Bs.query(margin, N - margin - 1);
    }
}

ll solve(ll eat) {
    if (eat >= N - 2) {
        ll mx = A[0];
        rep(i, N) mx = max(mx, A[i]);
        return mx;
    } else if (eat == N - 3) {
        ll mx = B[0];
        rep(i, N - 1) mx = max(mx, B[i]);
        return mx;
    }
    return solvemax(N - (eat + 1));
}

int main() {
    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];

    B.resize(N);
    rep(i, N - 1) B[i] = min(A[i], A[i + 1]);

    As = {N}, Bs = {N};
    repx(i, 1, N - 1) As[i] = max(A[i], min(A[i - 1], A[i + 1]));
    repx(i, 1, N - 2) Bs[i] = max(B[i], min(B[i - 1], B[i + 1]));
    As.init(), Bs.init();

    rep(k, N) {
        cout << solve(k) << " ";
    }
    cout << endl;
}
