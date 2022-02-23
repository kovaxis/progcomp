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

const ll MOD = 998244353;

int N;
int M[256][256];
vector<ll> fact;
string cs = "?BW";

ll binexp(ll a, ll m, ll M = MOD) {
    assert(m >= 0);
    ll res = 1 % M;
    while (m) {
        if (m & 1) res = (res * a) % M;
        a = (a * a) % M;
        m >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M = MOD) { return binexp(a, M - 2, M); }

ll choose(ll n, ll k, ll M = MOD) {
    return fact[n] * multinv(fact[k] * fact[n - k] % M, M) % M;
}

int cnt(vector<string> incl) {
    int c = 0;
    for (char i : cs)
        for (char j : cs) {
            bool ok = false;
            for (string& s : incl)
                ok |= (i == s[0] || s[0] == '_') && (j == s[1] || s[1] == '_');
            c += ok * M[i][j];
        }
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, N) {
        char c[2];
        rep(j, 2) cin >> c[j];
        M[c[0]][c[1]] += 1;
    }

    fact.resize(2 * N + 1);
    fact[0] = 1;
    rep(i, 1, 2 * N + 1) fact[i] = fact[i - 1] * i % MOD;

    ll ans = 0;

    int q = cnt({"?_", "_?"}) + cnt({"??"});
    int b = cnt({"B_", "_B"}) + cnt({"BB"});
    int w = cnt({"W_", "_W"}) + cnt({"WW"});
    if (b > N || w > N) {
        cout << "0\n";
        return 0;
    }

    cerr << "? = " << q << ", B = " << b << ", W = " << w << endl;

    ans += choose(q, N - b);  // N blacks, N whites
    ans %= MOD;

    ans -=
        binexp(2, cnt({"??"})) * binexp(0, cnt({"WW", "BB"}));  // all BW or WB
    ans += MOD;
    ans %= MOD;

    ans += binexp(0, cnt({"_B", "W_"}));  // all BW
    ans %= MOD;
    ans += binexp(0, cnt({"_W", "B_"}));  // all WB
    ans %= MOD;

    cout << ans << "\n";
}
