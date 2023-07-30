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

    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, N) cin >> A[i];

    vector<ll> B(N + 1);
    int desc = 0;
    rep(i, N) {
        ll x = 1;
        if (i > 0 && A[i] <= A[i - 1]) desc += 1;
        else desc = 0;
        if (desc >= 2) x = 0;
        B[i + 1] = B[i] + x;
    }

    rep(q, Q) {
        int l, r;
        cin >> l >> r;
        l--;

        ll ans = 0;

        int a = min(l + 10, r);

        int desc = 0;
        repx(i, l, a) {
            if (i > l) {
                if (A[i] <= A[i - 1]) desc += 1;
                else {
                    a = i;
                    break;
                }
            }
            if (desc >= 2) {
                a = i;
                break;
            }
            ans += 1;
        }

        ans += B[r] - B[a];

        cout << ans << "\n";
    }
}
