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

typedef long long ll;

const ll MOD = 998244353;

int count_divisors(int x) {
    int divs = 1;
    int i = 2;
    while (x > 1) {
        if (i * i > x) {
            divs *= 2;
            break;
        }
        int n = 1;
        while (x % i == 0) {
            x /= i;
            n += 1;
        }
        divs *= n;
        i += 1;
    }
    return divs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int total = 0;
    int nestacc = 0;

    int upto;
    cin >> upto;
    rep(n, 1, upto + 1) {
        // count divisors
        int divs = count_divisors(n);
        // nest
        total = (nestacc + divs) % MOD;
        nestacc = (2 * nestacc + divs) % MOD;
    }
    cout << total << endl;
}
