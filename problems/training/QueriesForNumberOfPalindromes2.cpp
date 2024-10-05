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

string s;
int N, P, Q;
vector<int> p;

int dpmem[5000][5000];
int dp(int i, int j) {
    if (i > j) return 0;
    int& c = dpmem[i][j];
    if (c != -1) return c;
    return c = dp(i, j - 1) + dp(i + 1, j) - dp(i + 1, j - 1) +
               (p[i + j] >= j - i + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> Q;
    N = s.size(), P = 2 * N - 1;

    p.resize(P);
    rep(i, P) {
        p[i] = i % 2;
        while (i - p[i] >= 0 && i + p[i] < P &&
               s[(i - p[i]) / 2] == s[(i + p[i]) / 2])
            p[i] += 2;
        p[i] -= 1;
    }

    rep(i, N) rep(j, N) dpmem[i][j] = -1;

    rep(q, Q) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << dp(l, r) << '\n';
    }
}
