#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

using T = ll;

struct Mat {
    int N, M;
    vector<vector<T>> v;

    Mat(int n, int m) : N(n), M(m), v(N, vector<T>(M)) {}
    Mat(int n) : Mat(n, n) { rep(i, N) v[i][i] = 1; }

    vector<T> &operator[](int i) { return v[i]; }
    const vector<T> &operator[](int i) const { return v[i]; }

    Mat operator*(const Mat &r) const {
        assert(M == r.N);
        int n = N, m = r.M, p = M;
        Mat a(n, m);
        rep(i, n) rep(j, m) {
            a[i][j] = T();                                   // neutral
            rep(k, p) a[i][j] = a[i][j] + v[i][k] * r[k][j]; // mul, add
        }
        return a;
    }

    Mat binexp(ll e) {
        assert(N == M);
        Mat a = *this, res(N); // neutral
        while (e) {
            if (e & 1) res = res * a; // mul
            a = a * a;                // mul
            e >>= 1;
        }
        return res;
    }

    friend ostream &operator<<(ostream &s, Mat &a) {
        rep(i, a.N) {
            rep(j, a.M) s << a[i][j] << " ";
            s << endl;
        }
        return s;
    }
};

int K, W;

int main() {
    int S;
    cin >> K >> W >> S;

    Mat tri(K + 1);
    rep(i, K + 1) rep(j, K + 1) tri[i][j] = 0;
    tri[0][0] = 1;
    rep(i, K) rep(j, K) {
        tri[i + 1][j] += tri[i][j];
        tri[i + 1][j + 1] += tri[i][j];
    }

    cerr << "triangle:" << endl
         << tri << endl;

    Mat x(K + 1, 1);
    x[0][0] = S;

    vector<bool> seen(W * W * W * W * W * W);
    int seencount = 0;
    while (true) {
        cerr << "at vector:" << endl
             << x << endl;

        int hash = 0;
        rep(i, K + 1) hash = W * hash + x[i][0];
        if (seen[hash]) break;
        seen[hash] = true;
        seencount += 1;

        x = tri * x;
        rep(i, K + 1) x[i][0] = x[i][0] % W;
    }

    cerr << "loop length: " << seencount << endl;
}
