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

vector<ll> D;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    D.resize(N);
    rep(i, N) cin >> D[i];

    ll prevl = 0, l = 0, prevr = 0, r = 0;
    bool left = true;
    sort(D.begin(), D.end());
    invrep(i, N) {
        ll x = left ? l : r;
        if (left)
            prevl = l;
        else
            prevr = r;
        l = min(l, x - D[i]);
        r = max(r, x + D[i]);
        left = !left;
    }
    ll ans = max(prevr - l, r - prevl);
    cout << ans << "\n";
}
