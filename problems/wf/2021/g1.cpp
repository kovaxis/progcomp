#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

using cd = complex<double>;
const double PI = acos(-1);

void fft_recur(vector<vector<cd>> &a, bool inv) {
    int N = a.size();
    if (N <= 1) return;
    assert(N == 1 << __builtin_ctz(N) && N == a[0].size());

    vector<vector<cd>> b[2][2];
    rep(i, 2) rep(j, 2) b[i][j] = vector<vector<cd>>(N / 2, vector<cd>(N / 2));
    rep(i, N) rep(j, N) b[i % 2][j % 2][i / 2][j / 2] = a[i][j];
    rep(i, 2) rep(j, 2) fft_recur(b[i][j], inv);

    double ang = 2 * PI / N * (inv ? -1 : 1);
    cd wl(cos(ang), sin(ang));
    cd wi = 1;
    rep(i, N / 2) {
        cd wj = 1;
        rep(j, N / 2) {
            cd u = b[0][0][i][j], v = b[1][0][i][j] * wi, s = b[0][1][i][j] * wj, t = b[1][1][i][j] * (wi * wj);
            a[i][j] = u + v + s + t;
            a[i + N / 2][j] = u - v + s - t;
            a[i][j + N / 2] = u + v - s - t;
            a[i + N / 2][j + N / 2] = u - v - s + t;
            wj *= wl;
        }
        wi *= wl;
    }

    if (inv) rep(i, N) rep(j, N) a[i][j] /= 4;
}

void fft(vector<vector<cd>> &a, bool inv) {
    int N = a.size(), k = 0, b;
    assert(N == 1 << __builtin_ctz(N) && a[0].size() == N);

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
        double ang = 2 * PI / l * (inv ? -1 : 1);
        cd wl(cos(ang), sin(ang));
        for (int ii = 0; ii < N; ii += l) {
            cd wi = 1;
            repx(i, ii, ii + l / 2) {
                for (int jj = 0; jj < N; jj += l) {
                    cd wj = 1;
                    repx(j, jj, jj + l / 2) {
                        cd u = a[i][j], v = a[i + l / 2][j] * wi, s = a[i][j + l / 2] * wj, t = a[i + l / 2][j + l / 2] * wi * wj;
                        a[i][j] = u + v + s + t;
                        a[i + l / 2][j] = u - v + s - t;
                        a[i][j + l / 2] = u + v - s - t;
                        a[i + l / 2][j + l / 2] = u - v - s + t;
                        wj *= wl;
                    }
                }
                wi *= wl;
            }
        }
    }

    if (inv)
        for (auto &y : a)
            for (cd &x : y) x /= N * N;
}

ll binexp(ll a, ll e, ll M) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a % M;
        a = a * a % M;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

const int MOD = 7340033, ROOT = 5;
void ntt(vector<vector<int>> &a, bool inv) {
    vector<int> wn;
    for (int p = ROOT; p != 1; p = (ll)p * p % MOD) wn.push_back(p);

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
        if (inv) wl = multinv(wl, MOD);
        for (int ii = 0; ii < N; ii += l) {
            ll wi = 1;
            repx(i, ii, ii + l / 2) {
                for (int jj = 0; jj < N; jj += l) {
                    ll wj = 1;
                    repx(j, jj, jj + l / 2) {
                        ll u = a[i][j], v = a[i + l / 2][j] * wi % MOD, s = a[i][j + l / 2] * wj % MOD, t = a[i + l / 2][j + l / 2] * wi % MOD * wj % MOD;
                        a[i][j] = (u + v + s + t) % MOD;
                        a[i + l / 2][j] = (2 * MOD + u - v + s - t) % MOD;
                        a[i][j + l / 2] = (2 * MOD + u + v - s - t) % MOD;
                        a[i + l / 2][j + l / 2] = (2 * MOD + u - v - s + t) % MOD;
                        wj = wj * wl % MOD;
                    }
                }
                wi = wi * wl % MOD;
            }
        }
    }

    ll m = multinv(N * N, MOD);
    if (inv)
        for (auto &y : a)
            for (int &x : y) x = (ll)x * m % MOD;
}

struct Mosaic {
    int N, M;
    vector<vector<int>> B;
    vector<vector<int>> A;
    int cnt;

    void read() {
        cin >> N >> M;
        B.assign(N, vector<int>(M));
        rep(i, N) rep(j, M) {
            cin >> B[i][j];
        }
        cerr << "read a " << N << "x" << M << " image" << endl;
    }

    void invert() {
        rep(i, N / 2) rep(j, M / 2) swap(B[i][j], B[N - i - 1][M - j - 1]);
    }

    void init(int color) {
        A.resize(1024);
        rep(i, 1024) A[i].assign(1024, 0);
        cnt = 0;
        rep(i, N) rep(j, M) {
            int c = B[i][j];
            if (c != color) continue;
            A[i][j] = 1;
            cnt += 1;
        }
    }

    bool is_match(int i, int j) {
        rep(c, 100) {
            // int n = A[i + N - 1][j + M - 1].real() + 0.5;
            int n = A[i + N - 1][j + M - 1];
            if (n != cnt) return false;
        }
        return true;
    }
};

double t() { return (double)clock() / CLOCKS_PER_SEC; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    Mosaic pat, hay;
    pat.read(), hay.read();
    pat.invert();

    int N = hay.N - pat.N + 1, M = hay.M - pat.M + 1;
    vector<pair<int, int>> ans;
    if (N > 0 && M > 0) {
        vector<vector<bool>> ok(N, vector<bool>(M, true));
        repx(c, 1, 101) {
            double t0 = t();
            pat.init(c), hay.init(c);
            double t1 = t();
            ntt(pat.A, false), ntt(hay.A, false);
            double t2 = t();
            rep(i, 1024) rep(j, 1024) pat.A[i][j] = (ll)pat.A[i][j] * hay.A[i][j] % MOD;
            double t3 = t();
            ntt(pat.A, true);
            double t4 = t();

            cerr << "convolved for color " << c << endl;
            // cerr << "init: " << (t1 - t0) << endl;
            // cerr << "fft: " << (t2 - t1) << endl;
            // cerr << "mult: " << (t3 - t2) << endl;
            // cerr << "inv fft: " << (t4 - t3) << endl;

            rep(i, N) rep(j, M) {
                if (!pat.is_match(i, j)) {
                    ok[i][j] = false;
                }
            }
        }
        rep(i, N) rep(j, M) if (ok[i][j]) ans.push_back({i, j});
    }

    cout << ans.size() << "\n";
    for (auto [i, j] : ans) {
        cout << i + 1 << " " << j + 1 << "\n";
    }
}
