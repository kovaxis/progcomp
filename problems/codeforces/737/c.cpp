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

ll MOD = 1000000007ll;

ll ex2[400005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    {
        ll val = 1;
        rep(i, 400005) {
            ex2[i] = val;
            val = (val * 2) % MOD;
        }
    }

    int T;
    cin >> T;
    rep(t, T) {
        ll N, K;
        cin >> N >> K;
        ll gt, eq;
        if (N % 2 == 0) {
            eq = (ex2[N - 1] + MOD - 1) % MOD;
            gt = 1;
        } else {
            eq = (ex2[N - 1] + 1) % MOD;
            gt = 0;
        }
        // ll geq = (ex2[N - 1] + N % 2) % MOD;
        ll partialways = 1;
        ll anycomb = 1;
        rep(k, K) {
            partialways = (gt * anycomb % MOD + eq * partialways % MOD) % MOD;
            anycomb = anycomb * ex2[N] % MOD;
        }

        cout << partialways << '\n';
    }
}
