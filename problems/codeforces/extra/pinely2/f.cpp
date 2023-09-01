#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<ll> A, B, L[2], R[2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];

        B.assign(N + 1, 0);
        rep(i, N) B[i + 1] = B[i] ^ A[i];

        rep(k, 2) L[k].assign(N + 1, 0), R[k].assign(N + 1, 0);

        string ans(N, '0');
        invrepx(n, 1, N + 1) {
            rep(l, N - n + 1) {
                // [l, l + n)
                int r = l + n;
                if ((L[0][l] & ~B[r]) || (L[1][l] & B[r]) || (R[0][r] & ~B[l]) || (R[1][r] & B[l]) || n == N) {
                    // this range is achievable
                    if (B[l] == B[r]) {
                        L[0][l] = 1;
                        L[1][l] = 1;
                        R[0][r] = 1;
                        R[1][r] = 1;
                    } else {
                        int bit = 63 - __builtin_clzll(B[l] ^ B[r]);
                        if (B[l] & (1ll << bit)) {
                            L[0][l] |= 1ll << bit;
                            R[1][r] |= 1ll << bit;
                        } else {
                            L[1][l] |= 1ll << bit;
                            R[0][r] |= 1ll << bit;
                        }
                    }
                    if (n == 1) {
                        ans[l] = '1';
                    }
                }
            }
        }

        cout << ans << "\n";
    }
}
