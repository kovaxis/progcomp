#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = ll(1e18) + 1;

ll N, M;
vector<ll> qpow;

ll mul(ll a, ll b) {
    __int128 c = (__int128)a * b;
    if (c > INF) return INF;
    return c;
}

ll add(ll a, ll b) {
    ll c = a + b;
    if (c > INF) return INF;
    return c;
}

ll getden(ll q, ll r) {
    qpow.resize(N);
    qpow[0] = 1;
    rep(i, N - 1) qpow[i + 1] = mul(qpow[i], q);
    ll sm = 0, rpow = 1;
    rep(i, N) {
        sm = add(sm, mul(rpow, qpow[N - 1 - i]));
        rpow = mul(rpow, r);
    }
    return sm;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (ll q = 2;; q++) {
        bool anysmall = false;
        for (ll r = 1; r < q; r++) {
            ll den = getden(q, r);
            if (den <= M) {
                anysmall = true;
                if (M % den == 0) {
                    cout << (q - r) << " " << q << endl;
                    return 0;
                }
            } else {
                break;
            }
        }
        if (!anysmall) break;
    }

    cout << "impossible" << endl;
}
