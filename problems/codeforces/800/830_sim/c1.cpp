#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, Q;
vector<ll> a, sm, xr;

ll getf(int l, int r) {
    return (sm[r] - sm[l]) - (xr[r] ^ xr[l]);
}

int findr(int ql, int qr, ll f) {
    int l = ql + 1, r = qr;
    while (l != r) {
        int m = (l + r) / 2;
        if (getf(ql, m) < f) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> Q;
        a.resize(N);
        rep(i, N) cin >> a[i];

        sm.resize(N + 1);
        rep(i, N) sm[i + 1] = sm[i] + a[i];
        xr.resize(N + 1);
        rep(i, N) xr[i + 1] = xr[i] ^ a[i];

        rep(q, Q) {
            int ql, qr;
            cin >> ql >> qr;
            ql -= 1;

            int ml, mr;
            ll mf = -1e18;
            repx(l, ql, qr) {
                ll f = getf(l, qr);
                int r = findr(l, qr, f);
                if (f > mf || (f == mf && r - l < mr - ml)) ml = l, mr = r, mf = f;
            }

            cout << ml + 1 << " " << mr << "\n";
        }
    }
}
