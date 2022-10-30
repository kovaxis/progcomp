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

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        vector<ll> a(N);
        rep(i, N) cin >> a[i];

        bool ok = true;

        if (N == 1 && a[0] != 0) ok = false;

        ll sm = 0;
        bool reachz = false;
        rep(i, N) {
            sm += a[i];
            if (sm < 0) ok = false;
            if (sm <= 0) reachz = true;
            if (reachz && sm != 0) ok = false;
        }
        if (!reachz) ok = false;

        cout << (ok ? "Yes" : "No") << "\n";
    }
}
