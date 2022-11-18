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

int N;
vector<bool> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) {
        char c;
        cin >> c;
        a[i] = (c == '1');
    }

    cerr << "read input" << endl;

    ll window = 0;
    ll ans = -1;
    rep(i, N) {
        ll bit = a[i];
        window <<= 1;
        if (bit == 0) {
            // if it is possible to cover this zero, constrain it
            cerr << "shift window for zero at " << i << " is " << window << endl;
            ll maybe = window & ans;
            if (maybe != 0) ans = maybe;
        }
        window |= bit;
    }
    cerr << "shift ans is " << ans << endl;

    int shift;
    rep(s, 64) if ((1ll << s) & ans) {
        shift = s;
        break;
    }
    cerr << "using shift " << shift << endl;

    bool nonzero = false;
    rep(i, N) {
        bool bit = a[i];
        if (i - shift >= 0) bit |= a[i - shift];
        nonzero |= bit;
        if (nonzero) cout << "01"[bit];
    }
    if (!nonzero) cout << "0";
    cout << "\n";
}
