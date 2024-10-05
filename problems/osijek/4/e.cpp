#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

const int M = 2.5e6;
const int MOD = 998244353;
vector<int> fact, invfact;

int binexp(int a, int e) {
    int r = 1;
    while (e) {
        if (e & 1) r = (ll)r * a % MOD;
        a = (ll)a * a % MOD;
        e /= 2;
    }
    return r;
}

int multinv(int a) { return binexp(a, MOD - 2); }

int choose(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (ll)fact[n] * invfact[n - k] % MOD * invfact[k] % MOD;
}

int multichoose(int n, int k) {
    if (k < 0 || n < 0) return 0;
    if (n == 0 && k == 0) return 1;
    return choose(n + k - 1, k);
}

int solve(int N) {
    int ans = 0;
    ans = (ans + (ll)fact[N] * multinv(2)) % MOD;
    ans = (ans + (ll)fact[N] * multichoose(N - 3, 2) % MOD * invfact[3]) % MOD;
    ans = (ans + (ll)multichoose(N - 5, 4) * multinv(8)) % MOD;
    ans = (ans + (ll)multichoose(N - 4, 3) * invfact[4]) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    fact.resize(M);
    fact[0] = 1;
    repx(i, 1, M) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact.resize(M);
    invfact[0] = 1;
    repx(i, 1, M) invfact[i] = (ll)invfact[i - 1] * multinv(i) % MOD;

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        cout << solve(N) << "\n";
    }
}
