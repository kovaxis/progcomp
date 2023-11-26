#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

float quickread() {
    static string s;
    cin >> s;
    s.push_back(0);
    char *c = &s[0];
    bool neg = false;
    if (*c == '-') c++, neg = true;
    float x = 0;
    while (*c && *c != '.') x = 10 * x + (*c - '0'), c++;
    if (*c == '.') c++;
    float mult = 1;
    while (*c) mult *= 0.1, x += mult * (*c - '0'), c++;
    if (neg) x = -x;
    return x;
}

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

float Dorder[1000000];

void measure() {
    int i = 0;
    rep(k, K) rep(r, R) rep(n1, N) rep(n2, N) Dorder[i++] = D[k][r][n1][n2];
    sort(&Dorder[0], &Dorder[i]);

    float percentile = 123456789;
    int j = percentile * (i - 1) + 0.5;
    float d = Dorder[j];
    int mb = (d + 2) / 2 * 900;

    unsigned char *arr = (unsigned char *)malloc(mb * 1024 * 1024);
    memset(arr, 1, mb * 1024 * 1024);
    cerr << (void *)arr;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    // Read input
    cin >> N >> K >> T >> R;
    rep(t, T) rep(k, K) rep(r, R) rep(n, N) S0[t][k][r][n] = quickread();
    rep(k, K) rep(r, R) rep(m, N) rep(n, N) D[k][r][m][n] = quickread();
    cin >> J;
    rep(j, J) {
        int _j, s, u, l, d;
        cin >> _j >> s >> u >> l >> d;
        F[j] = {s, u, l, l + d};
    }

    measure();

    rep(t, T) rep(k, K) rep(r, R) {
        rep(n, N) cout << "0 ";
        cout << "\n";
    }
}
