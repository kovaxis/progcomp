#include "../common.h"

// handle immutable range maximum queries (or any idempotent query) in O(1)
template <class T>
struct Sparse {
    vector<vector<T>> st;

    Sparse() {}

    void resize(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }
    // O(N log N) time
    // O(N log N) memory
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        rep(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));  // query op
    }

    // query maximum in the range [l, r) in O(1) time
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return max(st[i][l], st[i][r - (1 << i)]);  // query op
    }
};

#ifndef NOMAIN_SPARSE

Sparse<int> st;

void query(int l, int r, int ex) {
    int out = st.query(l - 1, r);
    cerr << "max [" << l << ", " << r << "] = " << out << endl;
    assert(out == ex);
}

int main() {
    st.resize(100000);
    rep(i, 100000) st.set(i, 7 * i % 11);
    rep(i, 20) cerr << st.query(i, i + 1) << " \n"[i == 19];
    st.init();
    query(1, 10, 10);
    query(1, 100000, 10);
    query(1, 3, 7);
    query(5, 14, 9);
    query(16, 21, 9);
    query(293, 9758, 10);
}

#endif
