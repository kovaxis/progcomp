#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll N, X;
vector<ll> a;

ll upto, acc;

bool bmp() {
    // cerr << "bumping upto from " << upto << " to " << upto + 1 << ", with acc = " << acc << endl;
    upto += 1;
    if (acc % upto != 0) return false;
    acc /= upto;
    return true;
}

bool solve() {
    sort(a.begin(), a.end());
    upto = 0, acc = 0;
    for (ll x : a) {
        bool bump = (upto < x);
        while (upto < x) {
            if (!bmp()) return false;
            if (upto >= X) return true;
        }
        acc += 1;
    }
    while (upto < X) {
        if (!bmp()) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> X;
    a.resize(N);
    rep(i, N) cin >> a[i];

    if (solve()) cout << "Yes\n";
    else cout << "No\n";
}
