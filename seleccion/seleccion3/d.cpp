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

const ll MOD = 1000000007;

ll N, x;
ll a[100001];
ll s, m;
ll b[100001];

ll binexp(ll a, ll m) {
    ll res = 1;
    while (m) {
        if (m & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        m >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> x;
    rep(i, N) {
        cin >> a[i];
        m = max(m, a[i]);
        s += a[i];
    }
    rep(i, N) b[i] = m - a[i];

    ll gcd = (s - m) % (MOD - 1);
    ll c = 0;
    rep(j, m) {
        rep(i, N) {
            if (b[i] == 0) c += 1;
            b[i] -= 1;
        }
        if (c % x == 0) {
            gcd = (gcd + 1) % (MOD - 1);
            c /= x;
        } else {
            break;
        }
    }

    cout << binexp(x, gcd) << endl;
}
