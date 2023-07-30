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

template <class T>
struct SparseMin {
    vector<vector<T>> st;

    T op(T a, T b) { return min(a, b); }

    SparseMin() {}

    void reset(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }

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
struct SparseMax {
    vector<vector<T>> st;

    T op(T a, T b) { return max(a, b); }

    SparseMax() {}

    void reset(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }

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
vector<int> A;
SparseMin<int> mn;
SparseMax<int> mx;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];

        mn.reset(N);
        rep(i, N) mn.set(i, A[i]);
        mn.init();

        mx.reset(N);
        rep(i, N) mx.set(i, A[i]);
        mx.init();

        ll ans = 0;
        rep(l, N) repx(r, l + 1, N + 1) {
            cerr << "subarray [" << l << ", " << r << ")" << endl;
            ans += r - l;
        }
        cerr << ans << " lengths of subarrays" << endl;

        rep(i, N + 1) {
            int r = i;
            rep(l, i) {
                int lmax = mx.query(l, i);
                while (r < N && mn.query(i, r + 1) > lmax) r++;
                cerr << r - i + 1 << " subarrays contains split-point " << i << " starting at " << l << endl;
                ans -= r - i + 1;
            }
        }

        cout << ans << "\n";
    }
}
