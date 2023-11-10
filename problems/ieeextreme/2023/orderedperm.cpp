#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

int N;
string R;
vector<ll> dp_prev, dp_now;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    cin >> R;
    assert(R.size() == N - 1);

    dp_prev.resize(N);
    dp_now.assign(N, 1);
    repx(i, 1, N) {
        swap(dp_now, dp_prev);
        if (R[i - 1] == '>') {
            // go down
            // use dp[i-1][k'] with k' > k
            ll acc = 0;
            rep(m, N - i) {
                acc = (acc + dp_prev[N - (i - 1) - 1 - m]) % MOD;
                dp_now[N - i - 1 - m] = acc;
            }
        } else {
            // go up
            ll acc = 0;
            rep(k, N - i) {
                acc = (acc + dp_prev[k]) % MOD;
                dp_now[k] = acc;
            }
        }
        // cerr << endl;
        // rep(k, N - i) cerr << dp[i][k] << " ways to build with n = " << i + 1 << ", below = " << k << ", above = " << N - i - 1 - k << endl;
    }

    cout << dp_now[0] << endl;
}
