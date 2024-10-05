#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

typedef complex<double> cd;
const double PI = acos(-1);

void fft(vector<cd> &a, bool inv) {
    int N = a.size(), k = 0, b;
    assert(N == 1 << __builtin_ctz(N));

    repx(i, 1, N) {
        for (b = N >> 1; k & b;) k ^= b, b >>= 1;
        if (i < (k ^= b)) swap(a[i], a[k]);
    }

    for (int l = 2; l <= N; l <<= 1) {
        double ang = 2 * PI / l * (inv ? -1 : 1);
        cd wl(cos(ang), sin(ang));
        for (int i = 0; i < N; i += l) {
            cd w = 1;
            rep(j, l / 2) {
                cd u = a[i + j], v = a[i + j + l / 2] * w;
                a[i + j] = u + v;
                a[i + j + l / 2] = u - v;
                w *= wl;
            }
        }
    }

    if (inv) rep(i, N) a[i] /= N;
}

vector<cd> convolve(vector<cd> a, vector<cd> b, int n) {
    reverse(b.begin(), b.end());
    n = 1 << (32 - __builtin_clz(2 * n - 1));
    a.resize(n), b.resize(n);
    fft(a, false), fft(b, false);
    rep(i, n) a[i] *= b[i];
    fft(a, true);
    return a;
}

int N;
string S;
vector<cd> V, K;
vector<int> ans;

void solve() {
    V.assign(N, 0), K.assign(N, 0);
    rep(i, N) {
        if (S[i] == 'V') V[i] = 1;
        if (S[i] == 'K') K[i] = 1;
    }

    vector<cd> clash = convolve(V, K, 2 * N);
    vector<bool> dists(N + 1);
    rep(i, 2 * N) {
        if (round(clash[i].real()) != 0) {
            int d = abs(i - (N - 1));
            dists[d] = true;
        }
    }

    ans.clear();
    repx(d, 1, N + 1) {
        bool ok = true;
        for (int dd = d; dd <= N; dd += d)
            if (dists[dd]) ok = false;
        if (ok) ans.push_back(d);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> S;
        N = S.size();
        solve();
        cout << ans.size() << "\n";
        for (int k : ans) cout << k << " ";
        cout << "\n";
    }
}
