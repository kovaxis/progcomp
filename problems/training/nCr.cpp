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

// 142857 = 3^3 * 11 * 13 * 37

// precompute subfactorials: n? = mult_{k=0}^{n} (k % p ? k : 1) (mod p^e).
// that is, the multiplication of all numbers <= n that are not multiples of p.
// computes them only until they start looping.
vector<pair<int, vector<int>>> subfacts;
void precompute(int p, int e) {
    int m = 1;
    rep(i, e) m *= p;
    auto& vp = subfacts[m];
    vector<int>& v = vp.second;

    map<pair<int, int>, int> seen;
    int acc = 1, n = 0;
    while (true) {
        // compute n! mod m
        // (but ignoring multiples of p)
        if (n % p) acc = acc * n % m;
        if (seen.count({n, acc})) {
            vp.first = seen[{n, acc}];
            break;
        }
        seen[{n, acc}] = v.size();
        v.push_back(acc);
        n = (n + 1) % m;
    }

    /*
    cerr << "facts for p = " << p << ", e = " << e << ", m = " << m << ":"
         << endl;
    cerr << "  loop = " << vp.first << ", count = " << v.size();
    rep(i, v.size()) {
        if (i % m == 0) cerr << endl << " ";
        int f = v[i];
        cerr << (f < 10 ? "  " : " ") << f;
    }
    cerr << endl;
    */
}

// compute the subfactorial n? mod m.
int subfact(int n, int m) {
    auto& vp = subfacts[m];
    int loop = vp.first;
    auto& v = vp.second;
    if (n < loop) return v[n];
    return v[loop + (n - loop) % (v.size() - loop)];
}

// compute the almost-factorial n! / p^k, where p^k is the highest power of p
// that divides n!.
int fact(int n, int p, int m) {
    int ans = 1;
    for (int x = n; x > 0; x /= p) ans = ans * subfact(x, m) % m;
    return ans;
}

// get the highest power of prime p that divides n!
ll getexp(int p, int n) {
    ll k = 0;
    for (ll x = p; n >= x; x *= p) k += n / x;
    return k;
}

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll multinv(ll a, ll M) {
    ll x, y;
    ll g = ext_gcd(a, M, x, y);
    assert(g == 1);
    return (x % M + M) % M;
}

// computes n choose r modulo the prime power p^e.
int solve_mod(int p, int e, int n, int r) {
    int m = 1;
    rep(i, e) m *= p;

    // cerr << " solving " << n << " choose " << r << " mod " << m << endl;

    ll ex = getexp(p, n) - getexp(p, r) - getexp(p, n - r);
    // cerr << "  p^k -> p = " << p << ", k = " << ex << endl;
    if (ex >= e) return 0;
    // cerr << "  " << n << "! = " << fact(n, p, m) << endl;
    // cerr << "  " << r << "! = " << fact(r, p, m) << endl;
    // cerr << "  " << n - r << "! = " << fact(n - r, p, m) << endl;
    int ans =
        fact(n, p, m) * multinv(fact(r, p, m) * fact(n - r, p, m) % m, m) % m;
    // cerr << "  ans = " << ans << " * " << p << "^" << ex << endl;
    rep(i, ex) ans = ans * p % m;
    // cerr << "  ans = " << ans << " mod " << m << endl;
    return ans;
}

pair<ll, ll> solve_crt(const vector<pair<ll, ll>>& eqs) {
    ll a0 = eqs[0].first, p0 = eqs[0].second;
    rep(i, 1, eqs.size()) {
        ll a1 = eqs[i].first, p1 = eqs[i].second;
        ll k1, k0;
        ll d = ext_gcd(p1, p0, k1, k0);
        a0 -= a1;
        if (a0 % d != 0) return {-1, -1};
        p0 = p0 / d * p1;
        a0 = a0 / d * k1 % p0 * p1 % p0 + a1;
        a0 = (a0 % p0 + p0) % p0;
    }
    return {a0, p0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    factsmod.resize(40);
    precompute(3, 3);
    precompute(11, 1);
    precompute(13, 1);
    precompute(37, 1);

    int Q;
    cin >> Q;
    rep(q, Q) {
        // cerr << endl;
        int n, r;
        cin >> n >> r;
        // cerr << "computing " << n << " choose " << r << endl;
        vector<pair<ll, ll>> eqs = {
            {solve_mod(3, 3, n, r), 27},
            {solve_mod(11, 1, n, r), 11},
            {solve_mod(13, 1, n, r), 13},
            {solve_mod(37, 1, n, r), 37},
        };
        pair<ll, ll> ans = solve_crt(eqs);
        assert(ans.second == 142857);
        // cerr << "ans = " << ans.first << endl;
        cout << ans.first << "\n";
    }
}
