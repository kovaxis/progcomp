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

ll K, X;

ll f(ll n) {
    if (n <= K) {
        return n * (n + 1) / 2;
    } else {
        n = 2 * K - n;
        return K * (K + 1) / 2 + K * (K - 1) / 2 - n * (n - 1) / 2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> K >> X;

        ll l = 1, r = 2 * K - 1;
        while (l != r) {
            int m = l + (r - l) / 2;
            if (f(m) < X) {
                l = m + 1;
            } else {
                r = m;
            }
        }

        cout << l << "\n";
    }
}
