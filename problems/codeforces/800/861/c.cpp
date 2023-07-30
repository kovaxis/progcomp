#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef __int128_t ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int countdigs(ll x) {
    int n = 0;
    while (x) n++, x /= 10;
    return n;
}

// find the smallest number in [l, inf) with only digits [a, b]
ll cansolve(ll L, ll a, ll b) {
    ll ans = L;
    bool quit = false;
    while (!quit && ans < ll(1) << 80) {
        ll p10 = 1;
        rep(i, countdigs(ans)) p10 *= 10;
        quit = true;
        while (p10 /= 10) {
            int d = ans / p10 % 10;
            if (d < a) {
                ans += (a - d) * p10;
                ans -= ans % p10;
            } else if (d > b) {
                ans += (a - d + 10) * p10;
                ans -= ans % p10;
                quit = false;
                break;
            }
        }
    }
    return ans;
}

ll solve(ll l, ll r) {
    rep(s, 10) {
        rep(a, 10) if (a + s < 10) {
            ll n = cansolve(l, a, a + s);
            // cerr << "with digits [" << a << ", " << a + s << "] in range [" << (long long)l << ", inf): " << (long long)n << endl;
            if (n <= r) return n;
        }
    }
    throw "could not find solution";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cerr << "ll is " << sizeof(ll) * 8 << " bits" << endl;

    int TC;
    cin >> TC;
    while (TC--) {
        long long l, r;
        cin >> l >> r;
        cout << (long long)solve(l, r) << "\n";
    }
}
