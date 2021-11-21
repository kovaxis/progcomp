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

const ll BMOD = 998244353;

struct Hash {
    size_t operator()(const ll& x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

template <class T, class U>
using umap = unordered_map<T, U, Hash>;

ll binexp(ll a, ll m, ll M) {
    assert(m >= 0);
    ll res = 1 % M;
    while (m) {
        if (m & 1) res = (res * a) % M;
        a = (a * a) % M;
        m >>= 1;
    }
    return res;
}

ll eulerphi(ll x) {
    ll phi = 1;
    ll k = 2;
    while (x > 1) {
        if (k * k > x) {
            phi *= x - 1;
            break;
        }
        ll k1 = 1, k0 = 0;
        while (x % k == 0) x /= k, k0 = k1, k1 *= k;
        phi *= k1 - k0;
        k += 1;
    }
    return phi;
}

ll dlog(ll a, ll b, ll M) {
    ll k = 1 % M, s = 0;
    while (true) {
        ll g = __gcd(a, M);
        if (g <= 1) break;
        if (b == k) return s;
        if (b % g != 0) return -1;
        b /= g, M /= g, s += 1, k = a / g * k % M;
    }
    ll N = sqrt(M) + 1;

    umap<ll, ll> r;
    ll baq = b;
    rep(q, N + 1) {
        r[baq] = q;
        baq = baq * a % M;
    }

    ll aN = binexp(a, N, M), aNp = k;
    rep(p, 1, N + 1) {
        aNp = aNp * aN % M;
        if (r.count(aNp)) return N * p - r[aNp] + s;
    }
    return -1;
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

    string ns;
    int T;
    cin >> T;
    rep(t, T) {
        ll X, M;
        cin >> ns >> X >> M;

        if (X == 1 || M == 1) {
            cout << "0\n";
            continue;
        } else if (X == 0 && ns != "1") {
            cout << "1\n";
            continue;
        }

        ll c = 0, M2 = M;
        while (M2 % 2 == 0) c += 1, M2 /= 2;
        ll M2phi = eulerphi(M2), BMODphi = BMOD - 1;
        ll Ncapped = 0, NM2 = 0, NBMOD = 0;
        for (char ch : ns) {
            ll v = ch - '0';
            Ncapped = min(10 * Ncapped + v, c);
            NM2 = (10 * NM2 + v) % M2phi;
            NBMOD = (10 * NBMOD + v) % BMODphi;
        }

        auto C2 = solve_crt(
            {{(1 << Ncapped) % (1 << c), 1 << c}, {binexp(2, NM2, M2), M2}});
        ll C = (C2.first - 1 + M) % M;
        ll D = dlog(C, X, M);
        if (D == -1) {
            cout << "-1\n";
            continue;
        }
        ll B = (binexp(2, D, BMOD) - 1 + BMOD) % BMOD *
               binexp(2, (NBMOD - 1 + BMODphi) % BMODphi, BMOD) % BMOD;
        cout << B << "\n";
    }
}
