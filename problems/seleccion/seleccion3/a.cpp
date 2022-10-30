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

int N;
int smin[100001];
int smax[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    int idx = 0;
    ll pairs = 0;
    rep(i, N) {
        int l;
        cin >> l;
        int mn = INT32_MAX, mx = INT32_MIN;
        int isasc = false;
        rep(j, l) {
            int x;
            cin >> x;
            if (x > mn) isasc = true;
            mn = min(mn, x);
            mx = max(mx, x);
        }
        if (isasc) {
            int count = 2 * (N - (i - idx)) - 1;
            // cerr << "sequence " << mn << ", " << mx << " produces " << count
            //     << " pairs\n";
            pairs += count;
        } else {
            smin[idx] = mn;
            smax[idx] = mx;
            idx += 1;
        }
    }

    sort(smin, smin + idx);
    sort(smax, smax + idx);

    rep(i, idx) {
        ll count = smax + idx - upper_bound(smax, smax + idx, smin[i]);
        // cerr << "sequence " << smin[i] << " produces " << count
        //     << " joint pairs\n";
        pairs += count;
    }

    cout << pairs << '\n';
}
