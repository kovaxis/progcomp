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

    int ts;
    cin >> ts;
    rep(t, ts) {
        long long a, b;
        cin >> a >> b;
        long long sh = max(min((2 * a - b) / 3, min(a / 2, b)), 0ll);
        long long sw = max(min((2 * b - a) / 3, min(a, b / 2)), 0ll);
        long long maxe = 0;
        if (sh * 2 + sw <= a && sh + 2 * sw <= b) {
            maxe = sh + sw;
        }
        if ((sh + 1) * 2 + sw <= a && sh + 1 + 2 * sw <= b) {
            maxe = sh + sw + 1;
        } else if (sh * 2 + sw + 1 <= a && sh + (sw + 1) * 2 <= b) {
            maxe = sh + sw + 1;
        }
        cout << maxe << "\n";
    }
}
