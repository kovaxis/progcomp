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

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll binexp(ll a, ll m, ll M) {
    assert(m >= 0);
    ll res = 1 % M;
    while (m) {
        if (m & 1) res = (res * a) % M;
        a = (a * a) % M;
        m >>= 1;
    }
    return res;
}

bool check_composite(ll n, ll a, ll d, int s) {
    ll x = binexp(a, d, n);
    if (x == 1 || x == n - 1) return false;
    rep(r, 1, s) {
        x = x * x % n;
        if (x == n - 1) return false;
    }
    return true;
}

bool isprime(ll n, int iter = 20) {
    if (n < 4) return n == 2 || n == 3;

    int s = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    rep(i, iter) {
        int a = 2 + rng() % (n - 3);
        if (check_composite(n, a, d, s)) return false;
    }
    return true;
}

ll solve(ll N) {
    ll r = N, b = 1;
    while (r % 2 == 0) r /= 2, b *= 2;
    if (r >= 2 * b + 1) return 2 * b;
    if (r == 1) return -1;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        ll N;
        cin >> N;
        cout << solve(N) << "\n";
    }
}
