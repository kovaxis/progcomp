#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

inline ll floordiv(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
}

inline ll ceildiv(ll a, ll b) {
    return a / b + ((a ^ b) >= 0 && a % b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int Q;
        cin >> Q;
        ll lo = 1, hi = 1e18;
        rep(q, Q) {
            int ty;
            cin >> ty;
            if (ty == 1) {
                // info
                ll a, b, n;
                cin >> a >> b >> n;
                ll newlo = (n - 1) * (a - b) + b + 1;
                ll newhi = (n - 1) * (a - b) + a;
                if (n == 1) newlo = 1;
                newlo = max(lo, newlo), newhi = min(hi, newhi);
                if (newlo <= newhi) {
                    lo = newlo, hi = newhi;
                    cout << "1";
                } else {
                    cout << "0";
                }
            } else if (ty == 2) {
                // question
                ll a, b;
                cin >> a >> b;
                ll nlo = max(1ll, ceildiv(lo - b, a - b));
                ll nhi = max(1ll, ceildiv(hi - b, a - b));
                if (nlo != nhi) {
                    cout << "-1";
                } else {
                    cout << nlo;
                }
            }
            cout << " \n"[q == Q - 1];
        }
    }
}
