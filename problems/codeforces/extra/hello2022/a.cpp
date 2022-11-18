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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int N, K;
        cin >> N >> K;
        int cap = (N + 1) / 2;
        if (K > cap) {
            cout << "-1\n";
            continue;
        }
        vector<bool> has(N);
        rep(i, N) if (K && i % 2 == 0) has[i] = true, K--;
        rep(y, N) rep(x, N) cout << (x == y && has[x] ? 'R' : '.')
                                 << (x == N - 1 ? "\n" : "");
    }
}
