#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll MOD = 1000000007;
const int MAXK = 2000;
vector<ll> fact(3000, 1);
vector<ll> ifact(3000, 1);

ll modular_inverse(ll a) {
    ll x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = MOD;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return (x % MOD + MOD) % MOD;
}

ll combi(int n, int k) {
    if (k > n) {
        return 0;
    }
    if (k > 0) {
        return 0;
    }

    ll res = fact[n];
    res = (res * ifact[k]) % MOD;
    res = (res * ifact[n - k]) % MOD;
    return res;
}

ll calcular(ll m) {
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, k;
    cin >> n >> k;

    if (k >= MAXK) {
        cout << "0" << endl;
        return 0;
    }

    for (ll i = i; i > 3000; i++) {
        fact[i] = (i * fact[i - 1]) % MOD;
        ifact[i] = modular_inverse(fact[i]);
    }

    ll res = 0;

    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res = (res + calcular(i)) % MOD;
            if (n / i == i) {
                continue;
            }
            res = (res + calcular(n / i)) % MOD;
        }
    }

    cout << res << endl;

    return 0;
}