
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll multinv_euc(ll a, ll M) {
    ll x, y;
    ll g = ext_gcd(a, M, x, y);
    assert(g == 1);
    return (x % M + M) % M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll B, L;

    cin >> B >> L;

    vector<ll> dig, Bs(L, 0);
    for (int i = 0; i < L; i++) {
        ll y;
        cin >> y;
        dig.push_back(y);
    }
    ll mul = 1, sum = 0;
    for (int i = L - 1; i >= 0; i--) {
        sum += mul * dig[i];
        sum %= (B + 1);

        Bs.push_back(mul);
        mul *= B;
        mul %= (B + 1);
    }
    reverse(Bs.begin(), Bs.end());
    bool o = 0;
    if (sum % (B + 1) == 0) {
        cout << "0 0\n";
        return 0;
    }
    for (int i = 0; i < L; i++) {
        ll aux = sum - (Bs[i] * dig[i]) % (B + 1) + B + 1;
        aux %= (B + 1);

        if (aux == 0) {
            cout << i + 1 << " 0\n";
            return 0;
        }
        aux = B + 1 - aux;

        ll inv = multinv_euc(Bs[i], B + 1);
        inv %= (B + 1);
        inv *= aux;
        inv %= (B + 1);

        if (inv < dig[i]) {
            cout << i + 1 << " " << inv << "\n";
            return 0;
        }
    }

    cout << "-1 -1\n";
}