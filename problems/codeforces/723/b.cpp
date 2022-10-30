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

int need[100];

bool check(int x) {
    int base = need[x % 100];
    x -= 11 * base;
    if (x < 0) return false;
    assert(x % 100 == 0);
    x /= 100;
    int count = base + (x / 11) * 100;
    x = x % 11;
    return x <= count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int mod100 = 0;
    rep(i, 100) {
        need[mod100] = i;
        mod100 = (mod100 + 11) % 100;
    }

    int ts;
    cin >> ts;
    rep(t, ts) {
        int x;
        cin >> x;
        if (check(x)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
