#include "../common.h"

using Matrix = vector<vector<ll>>;

Matrix identity(int N) {
    Matrix a(vector<ll>(N));
    rep(i, N) a[i][i] = 1;
    return a;
}

void multmatrix(Matrix& a, const Matrix& l, const Matrix& r) {
    int N = l.size(), M = r[0].size(), K = r.size();
    rep(i, N) rep(j, M) {
        ll x = 0;
        rep(k, K) x += (ll)l[i][k] * r[k][j] % MOD;
        a[i][j] = x % MOD;
    }
}

void binexp(Matrix& a, ll m, ll M) {
    // neutral element
    Matrix res(a.size()), tmp(a.size());
    rep(i, a.size()) res.a[i][i] = 1;
    while (m) {
        if (m & 1) tmp.mul(res, a), swap(res, tmp);  // multiplication
        tmp.mul(a, a), swap(tmp, a);                 // multiplication
        m >>= 1;
    }
    a = res;
}

void printmatrix(const Matrix& a) {
    int N = a.size(), M = a[0].size();
    rep(i, N) rep(j, M) {
        cerr << a[i][j];
        if (j == M - 1)
            cerr << endl;
        else
            cerr << " ";
    }
}

#ifndef NOMAIN_MATRIX

int main() {}

#endif
