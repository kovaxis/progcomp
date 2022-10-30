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

const ll MOD = 1000000007;

// Binary exponentiation modulo MOD.
ll binexp(ll a, ll m) {
    ll res = 1;
    while (m) {
        if (m & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        m >>= 1;
    }
    return res;
}

// Compute the modular multiplicative inverse, assuming MOD is prime.
ll multinv(ll a) { return binexp(a, MOD - 2); }

vector<int8_t> num;

// up_to, positive, result_k, includes_first
// permutations of the digits that result in `k mod 11`
// in other words, permutations of the digits such that the first `p` digits
// minus the next `n - p` digits result in `k mod 11`.
// if `f` is true, do not count the permutations that start with a number `0`.
ll dpmem[128][128][16][2];
ll dp(int n, int p, int k, bool f) {
    k = (k + 11) % 11;
    if (p < 0) return 0;
    if (n < p) return 0;
    if (n == 0) return k == 0;
    ll& cache = dpmem[n][p][k][f];
    if (cache != -1) return cache;

    int x = num[n - 1];
    ll res = 0;
    if (p > 0) {
        if (x != 0 || !f) res = (res + dp(n - 1, p - 1, k - x, false)) % MOD;
        res = (res + (p - 1) * dp(n - 1, p - 1, k - x, f) % MOD) % MOD;
    }
    int from = p;
    if (from == 0) {
        if (x != 0 || !f) res = (res + dp(n - 1, p, k + x, false)) % MOD;
        from += 1;
    }
    if (from <= n)
        res = (res + (n - from) * dp(n - 1, p, k + x, f) % MOD) % MOD;

    /*
    cerr << "permutations of \"";
    rep(i, num.size()) if (i < n) cerr << (int)num[i];
    else cerr << " ";
    cerr << "\" with " << p << " positives and " << (n - p)
         << " negatives that result in " << (k < 10 ? " " : "") << k
         << " mod 11 (" << (f ? "ex" : "in") << "cluding prefix zero): " << res
         << endl;
    */
    return cache = res;
}

ll counts[10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    while (cin >> s) {
        rep(n, s.size() + 1) rep(p, s.size() + 1) rep(k, 11) rep(f, 2)
            dpmem[n][p][k][f] = -1;
        num.resize(s.size());
        rep(i, s.size()) num[i] = s[i] - '0';
        // rep(i, s.size()) cerr << "-+"[i < (s.size() + 1) / 2];
        // cerr << endl;

        rep(i, 10) counts[i] = 0;
        ll divby = 1;
        rep(i, s.size()) {
            counts[num[i]] += 1;
            divby = (divby * counts[num[i]]) % MOD;
        }
        ll raw = dp(s.size(), (s.size() + 1) / 2, 0, true);
        // cerr << raw << " / " << divby << " = " << raw * multinv(divby) % MOD
        //     << "\n";
        cout << raw * multinv(divby) % MOD << '\n';
    }
}
