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

ll check(ll dist, ll maxdist) { return dist > maxdist ? INT64_MAX : dist; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        ll W, H;
        ll x1, y1, x2, y2;
        ll w, h;
        cin >> W >> H >> x1 >> y1 >> x2 >> y2 >> w >> h;
        ll mindist = min(min(min(check(h - y1, H - y2), check(h - H + y2, y1)),
                             check(w - x1, W - x2)),
                         check(w - W + x2, x1));
        mindist = max(0ll, mindist);
        if (mindist == INT64_MAX) {
            cout << "-1\n";
        } else {
            double distf = (double)mindist;
            cout << fixed << setw(9) << setprecision(9) << distf << '\n';
        }
    }
}
