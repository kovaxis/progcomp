#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#ifndef ENABLE_CERR
#define cerr \
    if (0) cerr
#endif

struct Frame {
    int thresh;
    int user;
    int l, r;
};

const float W = 192 / log(2.0);

int N, K, T, R, J;
float S0[1000][10][10][100]; // t, k, r, n
float D[10][10][100][100];   // k, r, n1, n2
Frame F[5000];               // j

void measure() {
    vector<int> cnt(T);
    rep(j, J) {
        Frame f = F[j];
        repx(t, f.l, f.r) cnt[t] += 1;
    }

    int mx = 0;
    rep(t, T) mx = max(mx, cnt[t]);

    cerr << "mx = " << mx << endl;

    unsigned char *arr = (unsigned char *)malloc(mx * 1024 * 1024);
    memset(arr, 1, mx * 1024 * 1024);
    repx(i, 1, mx * 1024 * 1024) arr[i] = arr[i - 1] + 1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    // Read input
    cin >> N >> K >> T >> R;
    rep(t, T) rep(k, K) rep(r, R) rep(n, N) cin >> S0[t][k][r][n];
    rep(k, K) rep(r, R) rep(m, N) rep(n, N) cin >> D[k][r][m][n];
    cin >> J;
    rep(j, J) {
        int _j, s, u, l, d;
        cin >> _j >> s >> u >> l >> d;
        F[j] = {s, u, l, l + d};
    }

    measure();
}
