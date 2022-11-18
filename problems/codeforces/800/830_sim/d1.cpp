#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int Q;
set<ll> X;
map<ll, ll> K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    X.insert(0);

    cin >> Q;
    rep(q, Q) {
        char t;
        cin >> t;
        if (t == '+') {
            ll x;
            cin >> x;

            X.insert(x);
        } else if (t == '?') {
            ll k;
            cin >> k;

            ll &ans = K[k];
            while (X.count(ans)) ans += k;

            cout << ans << "\n";
        }
    }
}
