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

using u32 = uint32_t;
using u64 = uint64_t;

// signed bigint
struct bigint {
    vector<u32> digits;
    u32 neg;

    bigint() : neg(0) {}
    bigint(ll x) : digits{lo(x), hi(x)}, neg(x < 0 ? ~0 : 0) { this->trim(); }
    bigint(vector<u32> d) : digits(d), neg(0) {}

    static u32 lo(u64 dw) { return (u32)dw; }
    static u32 hi(u64 dw) { return (u32)(dw >> 32); }

    // remove leading zeros from representation
    void trim() {
        while (digits.size() && digits.back() == neg) digits.pop_back();
    }

    void add(const bigint& rhs, u32 c = 0) {
        int ls = digits.size();
        int rs = rhs.digits.size();
        rep(i, max(ls, rs)) {
            if (i >= ls) digits.push_back(neg);
            u64 r = (u64)digits[i] + (i < rs ? rhs.digits[i] : rhs.neg) + c;
            digits[i] = lo(r), c = hi(r);
        }
        u64 ec = (u64)c + neg + rhs.neg;
        neg = ((hi(ec) ^ neg ^ rhs.neg) & 1 ? ~0 : 0);
        if (lo(ec) != neg) digits.push_back(lo(ec));
    }
    bigint& operator+=(const bigint& rhs) {
        this->add(rhs);
        return *this;
    }
    bigint& operator+=(u32 rhs) {
        this->add({}, rhs);
        return *this;
    }

    void negate() {
        rep(i, digits.size()) digits[i] = ~digits[i];
        neg = ~neg;
        this->add({}, 1);
    }

    bigint negated() const {
        bigint out = *this;
        out.negate();
        return out;
    }

    bigint& operator-=(const bigint& rhs) {
        this->negate();
        *this += rhs;
        this->negate();
        return *this;
    }

    bigint& operator*=(bigint& rhs) {
        static bigint lhs;
        swap(*this, lhs), digits.clear(), neg = 0;
        u32 r = rhs.neg, s = 0;
        if (lhs.neg) s ^= lhs.neg, lhs.negate();
        if (rhs.neg) s ^= rhs.neg, rhs.negate();
        rep(j, rhs.digits.size()) {
            u64 c = 0;
            int ls = digits.size();
            int rs = lhs.digits.size();
            rep(i, j, max(ls, rs + j)) {
                if (i >= ls) digits.push_back(0);
                u64 r =
                    (u64)digits[i] +
                    (u64)(i - j < rs ? lhs.digits[i - j] : 0) * rhs.digits[j] +
                    c;
                digits[i] = lo(r), c = hi(r);
            }
            if (c != 0) digits.push_back(c);
        }
        if (r) rhs.negate();
        if (s) negate();
        return *this;
    }

    bigint& operator/=(bigint& rhs) {
        divmod(rhs);
        return *this;
    }
    bigint& operator%=(bigint& rhs) {
        *this = divmod(rhs);
        return *this;
    }

    int divmod_trunc(int rhs) {
        u32 s = (rhs < 0 ? ~0 : 0) ^ this->neg, q = abs(rhs);
        u64 r = 0;
        if (this->neg) this->negate();
        invrep(i, digits.size()) {
            r = (r << 32) | digits[i];
            digits[i] = r / q, r %= q;
        }
        if (s) {
            this->negate();
            return -(int)r;
        }
        return (int)r;
    }

    // compares `this` with `rhs`
    //  `this < rhs`: -1
    //  `this == rhs`: 0
    //  `this > rhs`: 1
    int cmp(const bigint& rhs) const {
        if (neg && !rhs.neg) return -1;
        if (!neg && rhs.neg) return 1;
        int ls = digits.size(), rs = rhs.digits.size();
        invrep(i, max(ls, rs)) {
            u32 l = i < ls ? digits[i] : neg;
            u32 r = i < rs ? rhs.digits[i] : rhs.neg;
            if (l < r) return -1;
            if (l > r) return 1;
        }
        return 0;
    }

    bool operator==(const bigint& rhs) const { return cmp(rhs) == 0; }
    bool operator!=(const bigint& rhs) const { return cmp(rhs) != 0; }
    bool operator<(const bigint& rhs) const { return cmp(rhs) == -1; }
    bool operator>=(const bigint& rhs) const { return cmp(rhs) != -1; }
    bool operator>(const bigint& rhs) const { return cmp(rhs) == 1; }
    bool operator<=(const bigint& rhs) const { return cmp(rhs) != 1; }

    friend ostream& operator<<(ostream& s, const bigint& self) {
        if (self == bigint()) return s << "0";
        bigint x = self;
        if (x.neg) {
            x.negate();
            s << "-";
        }
        vector<int> digs;
        while (x != bigint()) digs.push_back(x.divmod_trunc(10));
        invrep(i, digs.size()) s << digs[i];
        return s;
    }

    // truncating division and modulo
    bigint divmod(bigint& rhs) {
        assert(rhs != bigint());
        u32 sr = rhs.neg, s = neg ^ rhs.neg;
        if (neg) negate();
        if (sr) rhs.negate();
        bigint l = 0, r = *this, x;
        r += 1u;
        while (l != r) {
            bigint m = l;
            m += r;
            rep(i, m.digits.size()) m.digits[i] =
                (m.digits[i] >> 1) |
                (i + 1 < m.digits.size() ? m.digits[i + 1] << 31 : 0);
            x = m, x *= rhs;
            if (x <= *this) {
                l = (m += 1);
            } else {
                r = m;
            }
        }
        l -= 1, swap(l, *this);
        r = *this, r *= rhs, l -= r;
        trim(), l.trim();
        if (sr) rhs.negate();
        if (s) negate(), l.negate();
        return l;
    }
};

struct Beast {
    ll linear;
    ll cycle;
    vector<ll> zoos;
};

int B, Z;

vector<vector<int>> pointers;
vector<vector<int>> path;
vector<Beast> info;

// calculate gcd(a, b).
// also, calculate x and y such that:
// a * x + b * y == gcd(a, b)
bigint ext_gcd(bigint a, bigint b, bigint& x, bigint& y) {
    if (b == bigint()) {
        x = 1, y = 0;
        return a;
    }
    bigint c = a.divmod(b), d = ext_gcd(b, c, y, x);
    a *= x, y -= a;
    return d;
}

// given a set of modular equations, each of the form `x = Ai (mod Pi)`, compute
// `x mod LCM(P0, P1, ..., Pn)`.
// returns a pair of `x` and `LCM(P0, P1, ..., Pn)`.
pair<bigint, bigint> solve_crt(const vector<pair<ll, ll>>& eqs) {
    bigint a0 = eqs[0].first, p0 = eqs[0].second;
    rep(i, 1, eqs.size()) {
        bigint a1 = eqs[i].first, p1 = eqs[i].second;
        bigint k1, k0;
        bigint d = ext_gcd(p1, p0, k1, k0);
        a0 -= a1;
        if (a0.divmod(d) != 0) return {-1, -1};
        p0 *= p1, p0 /= d;
        a0 *= k1, a0 *= p1, a0 += a1;
        a0 %= p0, a0 += p0, a0 %= p0;
    }
    return {a0, p0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> B >> Z;
    pointers.assign(B, vector<int>(Z + 1));
    info.resize(B);
    rep(b, B) {
        cin >> pointers[b][Z];
        rep(z, Z) cin >> pointers[b][z];
        rep(z, Z + 1) pointers[b][z] -= 1;
    }

    rep(b, B) {
        auto& seen = info[b].zoos;
        seen.assign(Z, -1);
        int P = 0;
        int x = pointers[b][Z];
        while (seen[x] == -1) {
            seen[x] = P++;
            x = pointers[b][x];
        }
        int k = seen[x];
        info[b].linear = k;
        info[b].cycle = P - k;
    }

    // pair.second == 0 -> time == pair.first
    // pair.second != 0 -> time % pair.second == pair.first
    vector<pair<ll, ll>> req(B);
    pair<bigint, int> ans = {0, -1};
    rep(z, Z) {
        ll mint = 0, fixt = -1;
        rep(b, B) {
            if (info[b].zoos[z] == -1) {
                fixt = -2;
                break;
            } else if (info[b].zoos[z] < info[b].linear) {
                req[b] = {info[b].zoos[z], 0};
                fixt = info[b].zoos[z];
            } else {
                req[b] = {info[b].zoos[z] % info[b].cycle, info[b].cycle};
                mint = max(mint, info[b].zoos[z]);
            }
        }

        // cerr << "crt equations:" << endl;
        // rep(b, B) cerr << "  x = " << req[b].first << " mod " <<
        // req[b].second
        //               << endl;
        // cerr << "  x >= " << mint << endl;
        // if (fixt != -1) cerr << "  x = " << fixt << endl;

        if (fixt != -1) {
            bool ok = fixt >= mint;
            rep(b, B) {
                if (req[b].second == 0)
                    ok = ok && fixt == req[b].first;
                else
                    ok = ok && fixt % req[b].second == req[b].first;
            }
            if (!ok) continue;
            if (ans.second == -1 || bigint(fixt) < ans.first)
                ans = {bigint(fixt), z};
            continue;
        }

        pair<bigint, bigint> sol = solve_crt(req);
        // cerr << "  solution: x = " << sol.first << " mod " << sol.second
        //     << endl;
        if (sol.first == bigint(-1)) continue;
        while (sol.first < bigint(mint)) sol.first += sol.second;
        if (ans.second == -1 || sol.first < ans.first) ans = {sol.first, z};
    }

    if (ans.second == -1)
        cout << "*" << endl;
    else
        cout << ans.second + 1 << " " << ans.first << endl;
}
