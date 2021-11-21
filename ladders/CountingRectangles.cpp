#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (ll i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (ll i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll mindiff = 99999;
    int minw, minh;
    rep(w, 1, 2002) {
        rep(h, 1, 2002) {
            ll rects = w * (w + 1) * h * (h + 1) / 4;
            ll diff = abs(rects - 2000000);
            if (diff < mindiff) {
                mindiff = diff;
                minw = w;
                minh = h;
            }
        }
    }
    cout << minw << "x" << minh << ": " << (minw * minh) << endl;
}
