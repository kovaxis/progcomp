#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

template <class T>
struct sparse {
    vector<vector<T>> st;

    sparse() {}
    sparse(vector<T> a) {
        int n = a.size();
        int npot = n <= 1 ? 1 : 32 - __builtin_clz(n);
        st.resize(npot);
        st[0] = a;
        rep(i, 1, npot) rep(j, n + 1 - (1 << i)) {
            st[i].push_back(binop(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));
        }
    }

    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return binop(st[i][l], st[i][r - (1 << i)]);
    }
};

int N, Q;
vector<ll> raw[2];
vector<ll> acc;

sparse<ll> accmin;
sparse<ll> accmax;

ll query(int l, int r) {
    ll accbase = l - 1 < 0 ? 0 : acc[l - 1];
    if (acc[r - 1] - accbase != 0) return -1;
    if (-accmin.query(l, r) - accbase < 0) return -1;
    return accmax.query(l, r) - accbase;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    rep(j, 2) raw[j].resize(N);
    rep(i, 2) rep(j, N) cin >> raw[i][j];
    acc.resize(N);
    rep(i, N) { acc[i] = (i - 1 < 0 ? 0 : acc[i - 1]) + raw[1][i] - raw[0][i]; }

    accmax = {acc};
    rep(i, N) acc[i] = -acc[i];
    accmin = {acc};
    rep(i, N) acc[i] = -acc[i];

    rep(q, Q) {
        int l, r;
        cin >> l >> r;
        cout << query(l - 1, r) << '\n';
    }
}
