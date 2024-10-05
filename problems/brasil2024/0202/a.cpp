#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int MOD = 1e9 + 7;

//  0
// 1 2
//  3
// 4 5
//  6

int L[7], H[7];
int ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    rep(i, 7) cin >> L[i];
    rep(i, 7) cin >> H[i];

    // count all
    ans = 1;
    rep(i, 7) {
        int x = max(0, H[i] - L[i] + 1);
        ans = (ll)ans * x % MOD;
    }

    // discount empty
    {
        int can = 1;
        rep(i, 7) if (L[i] > 0) can = 0;
        ans = (ans + MOD - can) % MOD;
    }

    // discount invalid single cycles
    for (int bm : vector<int>{
             (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3),
             (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6),
             (1 << 0) | (1 << 1) | (1 << 2) | (1 << 4) | (1 << 5) | (1 << 6),
         }) {
        int hi = 1e9 + 1, lo = 1;
        rep(i, 7) {
            if (bm & (1 << i)) {
                hi = min(hi, H[i]);
                lo = max(lo, L[i]);
            } else {
                if (L[i] > 0) hi = 0;
            }
        }
        int x = max(0, hi - lo + 1);
        ans = (ans + MOD - x) % MOD;
    }

    // discount invalid eight-cycles
    int a_lo = max(max(1, L[0]), max(L[1], L[2])), a_hi = min(H[0], min(H[1], H[2]));
    int b_lo = max(1, L[3]), b_hi = H[3];
    int c_lo = max(max(1, L[4]), max(L[5], L[6])), c_hi = min(H[4], min(H[5], H[6]));
    int discount = 0;
    repx(a, a_lo, a_hi + 1) repx(c, c_lo, c_hi + 1) {
        int invalid_b = a ^ c;
        discount += (b_lo <= invalid_b && invalid_b <= b_hi);
    }
    ans = (ans + MOD - discount) % MOD;

    cout << ans << endl;
}
