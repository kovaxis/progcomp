#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 9223372036737335297ll;

ll add(ll a, ll b) { return (__int128(a) + b) % MOD; }
ll sub(ll a, ll b) { return (__int128(a) + MOD - b) % MOD; }
ll mul(ll a, ll b) { return __int128(a) * b % MOD; }

ll binexp(ll a, ll e) {
    assert(e >= 0);
    ll res = 1;
    while (e) {
        if (e & 1) res = mul(res, a);
        a = mul(a, a);
        e >>= 1;
    }
    return res;
}

ll multinv(ll a) { return binexp(a, MOD - 2); }

const ll ROOT = binexp(3, (MOD - 1) >> 24);

void fft(vector<vector<ll>> &a, bool inv) {
    vector<ll> wn;
    for (ll p = ROOT; p != 1; p = mul(p, p)) wn.push_back(p);

    int N = a.size(), k = 0, b;
    assert(N == 1 << __builtin_ctz(N) && a[0].size() == N && N <= 1 << wn.size());

    repx(i, 1, N) {
        for (b = N >> 1; k & b;) k ^= b, b >>= 1;
        if (i < (k ^= b)) swap(a[i], a[k]);
    }
    k = 0;
    repx(j, 1, N) {
        for (b = N >> 1; k & b;) k ^= b, b >>= 1;
        if (j < (k ^= b)) rep(i, N) swap(a[i][j], a[i][k]);
    }

    for (int l = 2; l <= N; l <<= 1) {
        ll wl = wn[wn.size() - __builtin_ctz(l)];
        if (inv) wl = multinv(wl);
        for (int ii = 0; ii < N; ii += l) {
            ll wi = 1;
            repx(i, ii, ii + l / 2) {
                for (int jj = 0; jj < N; jj += l) {
                    ll wj = 1;
                    repx(j, jj, jj + l / 2) {
                        ll u = a[i][j], v = mul(a[i + l / 2][j], wi), s = mul(a[i][j + l / 2], wj), t = mul(a[i + l / 2][j + l / 2], mul(wi, wj));
                        a[i][j] = add(add(u, v), add(s, t));
                        a[i + l / 2][j] = add(sub(u, v), sub(s, t));
                        a[i][j + l / 2] = sub(add(u, v), add(s, t)) % MOD;
                        a[i + l / 2][j + l / 2] = sub(sub(u, v), sub(s, t));
                        wj = mul(wj, wl);
                    }
                }
                wi = mul(wi, wl);
            }
        }
    }

    ll q = multinv(N * N);
    if (inv) rep(i, N) rep(j, N) a[i][j] = mul(a[i][j], q);
}

void convolve(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    fft(a, false), fft(b, false);
    rep(i, 1024) rep(j, 1024) a[i][j] = mul(a[i][j], b[i][j]);
    fft(a, true);
}

struct Mosaic {
    int N, M;
    vector<vector<int>> B;

    void read() {
        cin >> N >> M;
        B.assign(N, vector<int>(M, 0));
        rep(i, N) rep(j, M) {
            cin >> B[i][j];
        }
        cerr << "read a " << N << "x" << M << " image" << endl;
    }

    void reverse() {
        rep(i, N) rep(j, (M + (i < N / 2)) / 2) swap(B[i][j], B[N - i - 1][M - j - 1]);
    }
};

double t() { return (double)clock() / CLOCKS_PER_SEC; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    Mosaic pat, hay;
    pat.read(), hay.read();
    pat.reverse();

    int I = hay.N - pat.N + 1, J = hay.M - pat.M + 1;
    vector<pair<int, int>> ans;
    if (I > 0 && J > 0) {
        vector<vector<ll>> R(I, vector<ll>(J));
        {
            ll p = 0;
            for (auto &row : pat.B)
                for (ll x : row) p += x * x * x;
            rep(i, I) rep(j, J) R[i][j] = p;
            cerr << "added P^3 term" << endl;
        }
        {
            vector<vector<ll>> A(1024, vector<ll>(1024)), B(1024, vector<ll>(1024));
            rep(i, pat.N) rep(j, pat.M) A[i][j] = pat.B[i][j];
            rep(i, hay.N) rep(j, hay.M) B[i][j] = hay.B[i][j] * hay.B[i][j];
            convolve(A, B);
            // cerr << "convolution:" << endl;
            // rep(i, hay.N) {
            //     rep(j, hay.M) cerr << A[i][j] << " ";
            //     cerr << endl;
            // }
            rep(i, I) rep(j, J) R[i][j] += A[i + pat.N - 1][j + pat.M - 1];
            cerr << "added P*T^2 term" << endl;
        }
        {
            vector<vector<ll>> A(1024, vector<ll>(1024)), B(1024, vector<ll>(1024));
            rep(i, pat.N) rep(j, pat.M) A[i][j] = pat.B[i][j] * pat.B[i][j];
            rep(i, hay.N) rep(j, hay.M) B[i][j] = hay.B[i][j];
            convolve(A, B);
            rep(i, I) rep(j, J) R[i][j] -= 2ll * A[i + pat.N - 1][j + pat.M - 1];
            cerr << "added P^2*T term" << endl;
        }
        rep(i, I) rep(j, J) if (R[i][j] == 0) ans.push_back({i, j});
    }

    cout << ans.size() << "\n";
    for (auto [i, j] : ans) {
        cout << i + 1 << " " << j + 1 << "\n";
    }
}
