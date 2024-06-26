#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts, n;
    cin >> ts;
    rep(t, ts) {
        cin >> n;
        if (n == 2) {
            cout << "-1\n";
            continue;
        }
        int lo = 0;
        int hi = (n * n + 1) / 2;
        rep(y, n) {
            rep(x, n) {
                if (x != 0) {
                    cout << " ";
                }
                if ((x + y) % 2 == 0) {
                    lo += 1;
                    cout << lo;
                } else {
                    hi += 1;
                    cout << hi;
                }
            }
            cout << '\n';
        }
    }
}
