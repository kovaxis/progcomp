#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1000000007;

struct Matrix {
    int N;
    vector<vector<int>> a;

    Matrix(int n) : N(n), a(N, vector<int>(N)) {}

    void print() const {
        rep(i, N) rep(j, N) {
            cout << a[i][j];
            if (j == N - 1)
                cout << endl;
            else
                cout << " ";
        }
    }

    void mul(const Matrix& l, const Matrix& r) {
        // cerr << "multiplying:" << endl;
        // l.print();
        // cerr << "x" << endl;
        // r.print();

        rep(i, N) rep(j, N) {
            ll x = 0;
            rep(k, N) x += (ll)l.a[i][k] * r.a[k][j] % MOD;
            a[i][j] = x % MOD;
        }
        // cerr << "=" << endl;
        // print();
    }
};

ll N, M;

void binexp(Matrix& a, ll m) {
    // neutral element
    Matrix res(M), tmp(M);
    rep(i, M) res.a[i][i] = 1;
    while (m) {
        if (m & 1) tmp.mul(res, a), swap(res, tmp);  // multiplication
        tmp.mul(a, a), swap(tmp, a);                 // multiplication
        m >>= 1;
    }
    a = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    Matrix trans(M);
    trans.a[0][0] = 1;
    trans.a[0][M - 1] = 1;
    rep(i, M - 1) trans.a[i + 1][i] = 1;
    binexp(trans, N);

    // cerr << "final matrix:" << endl;
    // trans.print();

    ll ans = trans.a[0][0];

    cout << ans << endl;
}
