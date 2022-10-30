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

int N, M, R, C;
vector<string> mat;

int solve() {
    R -= 1, C -= 1;
    if (mat[R][C] == 'B') return 0;
    rep(y, N) if (mat[y][C] == 'B') return 1;
    rep(x, M) if (mat[R][x] == 'B') return 1;
    rep(y, N) rep(x, M) if (mat[y][x] == 'B') return 2;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M >> R >> C;
        mat.assign(N, string(M, ' '));
        rep(y, N) cin >> mat[y];

        cout << solve() << "\n";
    }
}
