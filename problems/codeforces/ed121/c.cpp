#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

ll getdmg(ll start, ll finish) {
    ll len = finish - start + 1;
    return len * (len + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<ll> h(N), k(N);
        rep(i, N) cin >> k[i];
        rep(i, N) cin >> h[i];

        vector<pair<ll, ll>> atks(N);
        rep(i, N) atks[i] = {k[i] - h[i] + 1, k[i]};
        sort(atks.begin(), atks.end());
        ll lastbegin = 0, lastend = 0, dmg = 0;
        for (auto atk : atks) {
            if (atk.first <= lastend) {
                dmg -= getdmg(lastbegin, lastend);
            } else {
                lastbegin = atk.first;
            }
            lastend = max(lastend, atk.second);
            dmg += getdmg(lastbegin, lastend);
        }
        cout << dmg << "\n";
    }
}
