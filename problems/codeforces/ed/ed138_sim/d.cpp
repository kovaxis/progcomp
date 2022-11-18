#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

ll MOD = 998244353;

ll mul_big(ll x, ll big) {
    ll ans = 0, pow2 = 1;
    while (big != 0) {
        ans = (ans + (big & 1) * x * pow2 % MOD) % MOD;
        big >>= 1;
        pow2 = 2 * pow2 % MOD;
    }
    return ans;
}

ll N, M;

vector<bool> prime;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    prime.resize(N + 1, true);
    repx(i, 2, N + 1) {
        if (!prime[i]) continue;
        for (int j = 2 * i; j <= N; j += i) prime[j] = false;
    }

    ll all = 0, alldp = 1;
    repx(n, 1, N + 1) alldp = mul_big(alldp, M), all = (all + alldp) % MOD;
    cerr << "all = " << all << endl;

    ll acc = 0, unamb = 1, p = 1;
    repx(n, 1, N + 1) {
        if (prime[n]) {
            // if p * n > M, we're done, but beware of overflows
            if (n > M / p + 1) break;
            p *= n;
            if (M / p == 0) break;
        }
        unamb = mul_big(unamb, M / p);
        cerr << "unambiguous of length " << n << " = " << unamb << endl;
        acc = (acc + unamb) % MOD;
    }
    cerr << "total unambiguous = " << acc << endl;

    ll ans = (all - acc + MOD) % MOD;

    cout << ans << "\n";
}
