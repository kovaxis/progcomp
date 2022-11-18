#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll N, nearcost, farcost;
string as, bs;
vector<bool> a;

ll solve() {
    int ocnt = 0;
    rep(i, N) ocnt += a[i];
    if (ocnt % 2 != 0) return -1;

    if (farcost <= nearcost) {
        // prefer to swap far items
        if (ocnt == 2) {
            int first, last;
            rep(i, N) if (a[i]) first = i, i = N;
            rep(i, N) if (a[i]) last = i;
            if (first + 1 == last) {
                if (2 * farcost < nearcost) {
                    // use 2 far swaps
                    return 2 * farcost;
                } else {
                    // use 1 expensive near swap
                    return nearcost;
                }
            }
        }

        // use far swaps only
        return ocnt / 2 * farcost;
    } else {
        // prefer near swaps
        vector<ll> dp(N + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> nearcost >> farcost;
        cin >> as >> bs;

        a.resize(N);
        rep(i, N) a[i] = as[i] ^ bs[i];

        cout << solve() << "\n";
    }
}
