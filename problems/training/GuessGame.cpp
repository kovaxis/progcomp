// https://codeforces.com/problemset/problem/1864/E

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int MOD = 998244353;

ll binexp(ll a, ll e, ll M) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a % M;
        a = a * a % M;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

int N;
vector<int> A;
int ans;

void rec(int K, int L, int R) {
    if (K == 0 || L >= R) return;
    // cerr << "rec(" << K << "," << L << "," << R << ")" << endl;
    int cnt[32];
    rep(k, K + 1) cnt[k] = 0;
    repx(i, L, R) {
        int x = A[i] & ((1 << (K - 1)) - 1);
        int k = x == 0 ? 0 : 32 - __builtin_clz(x);
        cnt[k] += 1;
    }
    rep(k1, K + 1) repx(k2, k1 + 1, K + 1) {
        ans = (ans + 3ll * cnt[k1] % MOD * cnt[k2] % MOD) % MOD;
    }
    int l = L;
    rep(k, K + 1) {
        ans = (ans + (ll)cnt[k] * cnt[k] % MOD) % MOD;
        int r = l + cnt[k];
        rec(k, l, r);
        l = r;
    }
    assert(l == R);
}

int solve() {
    sort(A.begin(), A.end());

    ans = 0;
    rec(31, 0, N);

    return ans * multinv((ll)N * N % MOD, MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];
        cout << solve() << "\n";
    }
}
