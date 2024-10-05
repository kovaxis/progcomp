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

ll T, Q, g;
vector<ll> tps;

ll mod(ll x, ll m) {
    if (m == 0) return x;
    return (x % m + m) % m;
}

bool canreach_nomirror(ll z) { return mod(z, g) == 0; }

bool canreach(ll src, ll dst) {
    bool can = canreach_nomirror(dst - src);
    for (ll tp : tps) can = can || canreach_nomirror(dst - (2 * tp - src));
    return can;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        cin >> T >> Q;
        if (T == 0 || Q == 0) break;
        tps.resize(T);
        rep(t, T) cin >> tps[t];

        sort(tps.begin(), tps.end());
        g = 0;
        rep(t, T - 1) g = __gcd(g, 2 * (tps[t + 1] - tps[t]));

        rep(q, Q) {
            ll src, dst;
            cin >> src >> dst;
            if (canreach(src, dst))
                cout << "Y";
            else
                cout << "N";
            cout << " \n"[q == Q - 1];
        }
    }
}
