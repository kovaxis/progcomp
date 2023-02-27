#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

int N;
ll H;

vector<ll> pos;

ll dpmem[512][512];

// dp(l, r) = the least amount of bricks required to connect range [l, r)
// to ground
ll dp(int l, int r) {
    if (dpmem[l][r] != -1) return dpmem[l][r];

    if (r - l == 1) {
        return dpmem[l][r] = H;
    }

    ll inter = H - (pos[r - 1] - pos[l] + 1) / 2;
    ll res = INT64_MAX;
    repx(m, l + 1, r) {
        // split into two ranges: [l, m) and [m, r)
        ll ans = dp(l, m) + dp(m, r);
        if (inter >= 0) {
            // remove duplicate blocks
            ans -= inter + 1;
        }
        res = min(res, ans);
    }
    // cerr << "range [" << l + 1 << ", " << r << "] intersects at " << inter << " and uses " << res << " blocks" << endl;
    return dpmem[l][r] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> H;
    pos.resize(N);
    rep(i, N) cin >> pos[i];

    rep(l, N + 1) rep(r, N + 1) dpmem[l][r] = -1;

    cout << dp(0, N) << endl;
}
