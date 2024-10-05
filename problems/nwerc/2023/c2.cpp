#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < ll(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (ll i = b; i-- > ll(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr if (0) cerr

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) return x = 1, y = 0, a; // ?
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll multinv(ll a, ll m) {
    ll x, y;
    ext_gcd(a, m, x, y);
    return ((x % m) + m) % m;
}

ll N, n, Q, A, B;
vector<ll> at;

void apply() {
    vector<ll> mv(N, 1e9);
    vector<ll> at2(N, -1);
    rep(x, N) if (at[x] != -1) {
        ll x2 = ((ll)A*x + B) % N;
        ll m = (x2 - x + N) % N;
        if (m < mv[x2]) at2[x2] = at[x], mv[x2] = m;
    }
    at = at2;
    A = 1, B = 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> Q;

    at.resize(N);
    rep(i, N) at[i] = i;

    A = 1, B = 0;
    n = N;

    while(Q--) {
        string qx;
        ll x;
        cin >> qx >> x;
        x %= N;

        if (qx == "+") {
            B = (B + x) % N;
            cerr << "added " << x << endl;
        }
        if (qx == "*") {
            ll g = __gcd(x, n);
            A = (ll)A * x % N;
            B = (ll)B * x % N;
            if (g == 1) {
                cerr << "simple mult by " << x << endl;
            }else{
                cerr << "complex mult by " << x << ", reducing by " << g << endl;
                apply();
                n /= g;
            }
        }
        if (qx == "?") {
            ll x2 = (x + N - B) % N;
            ll x3 = x2 / (N / n);
            ll x4 = x3 * (ll)multinv(A, n) % n;
            ll x5 = x4 * (N / n) + x2 % (N / n);
            ll i = at[x5];
            cout << (i == 0 ? N : i) << "\n";
        }
    }
}
