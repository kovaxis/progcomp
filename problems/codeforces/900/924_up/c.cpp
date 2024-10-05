#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ll X, Y;
        cin >> X >> Y;
        set<ll> ans;
        for (ll k = 2; k * k <= X; k += 1) {
            cerr << "trying k = " << k << endl;
            ll l = 2 * k - 2;
            if (X % l == Y % l || ((2 * k - X) % l + l) % l == Y) {
                cerr << "got " << k << endl;
                ans.insert(k);
            }
        }
        for (ll n = 1; n * n <= X; n += 1) {
            cerr << "trying " << n << " cycles" << endl;
            ll num = X - Y + 2 * n;
            ll den = 2 * n;
            if (num % den == 0) {
                cerr << "got " << num / den << endl;
                ans.insert(num / den);
            }
        }
        for (ll n = 0; n * n <= X; n += 1) {
            cerr << "trying " << n << " rev cycles" << endl;
            ll num = X + Y + 2 * n;
            ll den = 2 + 2 * n;
            if (num % den == 0) {
                cerr << "got " << num / den << endl;
                ans.insert(num / den);
            }
        }

        int cnt = 0;
        for (ll k : ans) {
            if (k >= 2 && k >= Y) cnt += 1;
        }
        cout << cnt << "\n";
    }
}
