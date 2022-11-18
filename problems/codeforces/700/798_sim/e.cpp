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

struct Dsu {
    vector<int> p, r;

    // initialize the disjoint-set-union to all unitary sets
    void reset(int N) {
        p.resize(N), r.assign(N, 0);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two sets with leaders `i` and `j`
    // note: `i` and `j` must be GROUP LEADERS
    void unite(int i, int j) {
        if (i == j) return;
        if (r[i] > r[j]) swap(i, j);
        if (r[i] == r[j]) r[j] += 1;
        p[i] = j;
    }
};

int N;
vector<int> a;
Dsu dsu;
vector<bool> found;

// check if there is only 1 component.
bool check() {
    dsu.reset(30);
    found.assign(30, true);
    rep(j, N) {
        if (a[j] == 0) return false;
        int last = -1;
        rep(l, 30) if ((a[j] >> l) & 1) {
            found[l] = false;
            if (last != -1) dsu.unite(dsu.find(l), dsu.find(last));
            last = l;
        }
    }
    int cnt = 0;
    rep(l2, 30) {
        int l = dsu.find(l2);
        cnt += !found[l], found[l] = true;
    }
    cerr << "  resulted in " << cnt << " components" << endl;
    return cnt == 1;
}

int solve() {
    int K = 0;
    rep(i, N) if (a[i] == 0) a[i] = 1, K += 1;

    // try in 0 steps
    cerr << "checking 0 steps..." << endl;
    if (check()) return K;

    // try in 1 step
    rep(i, N) rep(k, 2) {
        a[i] += k * 2 - 1;
        cerr << "checking a[" << i << "] += " << k * 2 - 1 << endl;
        if (check()) return K + 1;
        a[i] -= k * 2 - 1;
    }

    // solve in 2 steps
    int mx = -1, mxi;
    rep(i, N) {
        int l = __builtin_ctz(a[i]);
        if (l >= mx) mx = l, mxi = i;
    }
    a[mxi] -= 1;
    int mxj;
    mx = -1;
    rep(i, N) {
        int l = __builtin_ctz(a[i]);
        if (l >= mx) mx = l, mxj = i;
    }
    a[mxj] += 1;
    cerr << "checking a[" << mxi << "] -= 1, a[" << mxj << "] += 1" << endl;
    assert(check());
    return K + 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];
        cout << solve() << "\n";
        rep(i, N) cout << a[i] << " \n"[i == N - 1];
    }
}
