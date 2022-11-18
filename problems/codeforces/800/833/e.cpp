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

ll binexp(ll a, ll e, ll M) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a;
        a = a * a;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

// calculate gcd(a, b).
// also, calculate x and y such that:
// a * x + b * y == gcd(a, b)
//
// time: O(log min(a, b))
// (ignoring complexity of arithmetic)
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// compute inverse with any M.
// a and M must be coprime for inverse to exist!
ll multinv_euc(ll a, ll M) {
    ll x, y;
    ext_gcd(a, M, x, y);
    return x;
}

// multiply two big numbers (~10^18) under a large modulo, without resorting to
// bigints.
ll bigmul(ll x, ll y, ll M) {
    ll z = 0;
    while (y) {
        if (y & 1) z = (z + x) % M;
        x = (x << 1) % M, y >>= 1;
    }
    return z;
}

struct Mod {
    int a;
    static const int M = 1e9 + 7;

    Mod(ll aa) : a((aa % M + M) % M) {}
    // Mod(ll aa, ll m) : M(m), a((aa % M + M) % M) {} // dynamic modulus

    Mod operator+(Mod rhs) const { return (a + rhs.a) % M; }
    Mod operator-(Mod rhs) const { return (a - rhs.a + M) % M; }
    Mod operator-() const { return Mod(0) - *this; }
    Mod operator*(Mod rhs) const { return (ll)a * rhs.a % M; }

    Mod operator+=(Mod rhs) { return *this = *this + rhs; }
    Mod operator-=(Mod rhs) { return *this = *this - rhs; }
    Mod operator*=(Mod rhs) { return *this = *this * rhs; }

    Mod bigmul(ll big) const { return ::bigmul(a, big, M); }

    Mod binexp(ll e) const { return ::binexp(a, e, M); }
    Mod multinv() const { return ::multinv(a, M); } // prime M
    // Mod multinv() const { return ::multinv_euc(a, M); } // possibly composite M
};

int N, M;
vector<int> a, pl, pr;
vector<vector<Mod>> dp;

void build(int i) {
    if (pl[i] != -1) build(pl[i]);
    if (pr[i] != N) build(pr[i]);

    dp[i].assign(M + 1, 0);
    repx(m, 1, M + 1) {
        Mod l = pl[i] == -1 ? 1 : dp[pl[i]][m - 1];
        Mod r = pr[i] == N ? 1 : dp[pr[i]][m];
        dp[i][m] = dp[i][m - 1] + l * r;
    }
}

Mod solve() {
    // build pl
    {
        pl.assign(N, -1);
        vector<pair<int, int>> stk;
        stk.push_back({1e9, N});
        invrep(i, N) {
            while (a[i] >= stk.back().first) stk.pop_back();
            if (stk.back().second != N) pl[stk.back().second] = i;
            stk.push_back({a[i], i});
        }
    }

    // build pr
    {
        pr.assign(N, N);
        vector<pair<int, int>> stk;
        stk.push_back({1e9, -1});
        rep(i, N) {
            while (a[i] > stk.back().first) stk.pop_back();
            if (stk.back().second != -1) pr[stk.back().second] = i;
            stk.push_back({a[i], i});
        }
    }

    cerr << "pl:";
    rep(i, N) cerr << " " << pl[i];
    cerr << endl;
    cerr << "pr:";
    rep(i, N) cerr << " " << pr[i];
    cerr << endl;

    dp.assign(N, {});
    int mx = -1e9, mxi;
    rep(i, N) if (a[i] > mx) mx = a[i], mxi = i;
    build(mxi);
    return dp[mxi][M];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        a.resize(N);
        rep(i, N) cin >> a[i];

        cout << solve().a << "\n";
    }
}
