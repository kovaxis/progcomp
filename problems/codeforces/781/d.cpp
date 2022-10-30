#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        ll cur = 0;
        rep(k, 30) {
            ll add = (1 << k) - cur;
            cout << "? " << add << " " << add + (1 << (k + 1)) << endl;
            ll y;
            cin >> y;
            if (y >= (1 << (k + 1))) {
                cur |= 1 << k;
            } else {
            }
        }
        cout << "! " << cur << endl;
    }
}
