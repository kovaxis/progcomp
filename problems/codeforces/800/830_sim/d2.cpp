#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int Q;

// K: x's in set
// V: which k's are affected by this x
map<ll, set<ll>> X;

// K: seen k
// V: next possible answer, holes
map<ll, pair<ll, set<ll>>> K;

ll query(ll k) {
    auto &[nxt, holes] = K[k];

    while (holes.size() != 0) {
        ll hole = *holes.begin();
        if (X.count(hole)) {
            // hole was filled back
            X[hole].insert(k);
            holes.erase(hole);
        } else {
            // use hole
            return hole;
        }
    }

    // find next values
    while (X.count(nxt)) {
        X[nxt].insert(k);
        nxt += k;
    }

    // use next value
    return nxt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    X[0] = {};

    cin >> Q;
    rep(q, Q) {
        char t;
        cin >> t;
        if (t == '+') {
            ll x;
            cin >> x;

            X[x] = {};
        } else if (t == '-') {
            ll x;
            cin >> x;

            for (ll k : X[x]) {
                // insert a hole
                K[k].second.insert(x);
            }

            X.erase(x);
        } else if (t == '?') {
            ll k;
            cin >> k;

            cout << query(k) << "\n";
        }
    }
}
