#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Basis {
    int A[21];

    Basis() { rep(b, 21) A[b] = 0; }

    bool add(int x) {
        invrep(b, 21) {
            if ((x >> b) & 1) {
                if (A[b]) {
                    x ^= A[b];
                } else {
                    A[b] = x;
                    return true;
                }
            }
        }
        return false;
    }

    int count() {
        int n = 0;
        rep(b, 21) if (A[b]) n += 1;
        return n;
    }

    void merge(const Basis &b) {
        rep(k, 21) {
            if (!A[k]) A[k] = b.A[k];
        }
    }
};

struct Sparse {
    vector<vector<Basis>> st;

    Basis op(Basis a, Basis b) {
        a.merge(b);
        return a;
    }

    Sparse() {}
    Sparse(int N) : st{vector<Basis>(N)} {}

    Basis &operator[](int i) { return st[0][i]; }

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
    Basis query(int l, int r) {
        if (r <= l) return {};
        int i = 31 - __builtin_clz(r - l);
        return op(st[i][l], st[i][r - (1 << i)]); // query op
    }
};

const ll MOD = 1e9 + 7;

int N;
vector<int> A;
Sparse sparse;

int independent(int l, int r) {
    return sparse.query(l, r).count();
}

int min_width_for_size(int L, int K) {
    int l = L, r = N;
    while (l != r) {
        int m = (l + r) / 2;
        if (independent(L, m + 1) < K) l = m + 1;
        else r = m;
    }
    return r;
}

// first the first position `j` such that in basis(A_j, ..., A_i) A_i is independent when added
int find_start(int i) {
    int l = 0, r = i + 1;
    while (l != r) {
        int m = (l + r) / 2;
        if (sparse.query(m, i).add(A[i])) r = m;
        else l = m + 1;
    }
    return l;
}

ll pow2(int k) {
    ll r = 1;
    while (k--) r = r * 2 % MOD;
    return r;
}

ll solve() {
    double t = (double)clock() / CLOCKS_PER_SEC;
    sparse = {N};
    rep(i, N) sparse[i].add(A[i]);
    sparse.init();
    double t1 = (double)clock() / CLOCKS_PER_SEC;

    cerr << "sparse: " << (t1 - t) << endl;

    cerr << "to the left" << endl;

    vector<int> startsfrom(N);
    vector<vector<int>> evs(N + 1);
    rep(i, N) {
        startsfrom[i] = find_start(i);
        // cerr << i << " starts from " << startsfrom[i] << endl;
        evs[startsfrom[i]].push_back(i);
    }

    cerr << "to the right" << endl;
    ll ans = 0;
    set<int> basis;
    rep(i, N) {
        for (int new_base : evs[i]) basis.insert(new_base);
        if (basis.size() && *basis.begin() < i) basis.erase(basis.begin());

        vector<int> basis_vec;
        basis_vec.push_back(i);
        for (int b : basis) basis_vec.push_back(b);
        basis_vec.push_back(N);

        // cerr << "at " << i << ", basis is:";
        // for (int x : basis_vec) cerr << " " << x;
        // cerr << endl;

        rep(k, basis_vec.size() - 1) {
            // cerr << "  ranges that end (inclusively) somewhere at [" << basis_vec[k] << ", " << basis_vec[k + 1] << ") have size " << k << endl;
            ans = (ans + (basis_vec[k + 1] - basis_vec[k]) * pow2(k) % MOD) % MOD;
        }
    }

    /*
    ll ans = 0;
    rep(l, N) {
        // cerr << "checking ranges that start at " << l << endl;
        int R[22];
        rep(k, 21) {
            R[k] = min_width_for_size(l, k);
        }
        R[21] = N;
        rep(k, 21) {
            // cerr << "  ranges that end (inclusively) somewhere at [" << R[k] << ", " << R[k + 1] << ") have size " << k << endl;
            ans = (ans + (R[k + 1] - R[k]) * pow2(k) % MOD) % MOD;
        }
    }
    */

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> N;
        A.resize(N);
        rep(i, N) {
            cin >> A[i];
        }

        cout << solve() << endl;
    }
}
