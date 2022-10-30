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

struct bigint {
    vector<uint32_t> digits;
    uint32_t neg;

    bigint() : neg(0) {}
    bigint(ll x) : digits{lo(x), hi(x)}, neg(x < 0 ? ~0 : 0) { this->trim(); }
    bigint(vector<uint32_t> d) : digits(d), neg(0) {}

    static uint32_t lo(uint64_t dw) { return (uint32_t)dw; }
    static uint32_t hi(uint64_t dw) { return (uint32_t)(dw >> 32); }

    // remove leading zeros from representation
    void trim() {
        while (digits.size() && digits.back() == neg) digits.pop_back();
    }

    void add(const bigint& rhs, uint32_t c = 0) {
        int ls = digits.size();
        int rs = rhs.digits.size();
        rep(i, max(ls, rs)) {
            if (i >= ls) digits.push_back(neg);
            uint64_t r =
                (uint64_t)digits[i] + (i < rs ? rhs.digits[i] : rhs.neg) + c;
            // cerr << "adding lhs[" << i << "] = " << digits[i] << " + rhs[" <<
            // i
            //     << "] = " << (i < rs ? rhs.digits[i] : rhs.neg)
            //     << " + carry = " << c << " to obtain " << r << endl;
            digits[i] = lo(r), c = hi(r);
        }
        // cerr << "finished with carry = " << c << endl;
        uint64_t ec = (uint64_t)c + neg + rhs.neg;
        // cerr << "extended carry is " << ec << endl;
        neg = ((hi(ec) ^ neg ^ rhs.neg) & 1 ? ~0 : 0);
        // cerr << "sign is " << neg << endl;
        if (lo(ec) != neg) digits.push_back(lo(ec));
    }
    void operator+=(const bigint& rhs) { this->add(rhs); }
    void operator+=(uint32_t rhs) { this->add({}, rhs); }

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

    void operator-=(const bigint& rhs) {
        this->negate();
        *this += rhs;
        this->negate();
    }

    void operator*=(bigint& rhs) {
        static bigint lhs;
        swap(*this, lhs);
        digits.clear();
        uint32_t r = rhs.neg, s = 0;
        if (lhs.neg) s ^= lhs.neg, lhs.negate();
        if (rhs.neg) s ^= rhs.neg, rhs.negate();
        rep(j, rhs.digits.size()) {
            uint64_t c = 0;
            int ls = digits.size();
            int rs = lhs.digits.size();
            rep(i, j, max(ls, rs + j)) {
                if (i >= ls) digits.push_back(0);
                uint64_t r = (uint64_t)digits[i] +
                             (uint64_t)(i - j < rs ? lhs.digits[i - j] : 0) *
                                 rhs.digits[j] +
                             c;
                digits[i] = lo(r), c = hi(r);
            }
            if (c != 0) digits.push_back(c);
        }
        neg = 0;
        if (r) rhs.negate();
        if (s) negate();
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
            uint32_t l = i < ls ? digits[i] : neg;
            uint32_t r = i < rs ? rhs.digits[i] : rhs.neg;
            if (l < r) return -1;
            if (l > r) return 1;
        }
        return 0;
    }

    bool operator==(const bigint& rhs) { return cmp(rhs) == 0; }
    bool operator!=(const bigint& rhs) { return cmp(rhs) != 0; }
    bool operator<(const bigint& rhs) { return cmp(rhs) == -1; }
    bool operator>=(const bigint& rhs) { return cmp(rhs) != -1; }
    bool operator>(const bigint& rhs) { return cmp(rhs) == 1; }
    bool operator<=(const bigint& rhs) { return cmp(rhs) != 1; }
};

struct Poly {
    vector<ll> coef;

    Poly() {}
    Poly(int N) : coef(N) {}

    Poly operator*(const Poly& rhs) const {
        const auto &a = this->coef, b = rhs.coef;
        if (a.size() == 0 || b.size() == 0) return {};
        Poly out(a.size() + b.size() - 1);
        rep(i, a.size()) rep(j, b.size()) out.coef[i + j] += a[i] * b[j];
        return out;
    }

    Poly operator+(const Poly& rhs) const {
        const auto &a = this->coef, b = rhs.coef;
        Poly out(max(a.size(), b.size()));
        auto& c = out.coef;
        rep(i, c.size()) c[i] =
            (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
        return out;
    }

    Poly operator-() const {
        Poly out = *this;
        for (auto& c : out.coef) c = -c;
        return out;
    }
};

string raw;
int nxt;
int hidigit;
vector<ll> poly;

Poly readnum() {
    Poly p;
    while (nxt < raw.size() && raw[nxt] >= '0' && raw[nxt] <= '9') {
        p.coef.insert(p.coef.begin(), raw[nxt] - '0');
        hidigit = max(hidigit, raw[nxt] - '0');
        nxt += 1;
    }
    return p;
}

Poly readmul() {
    Poly p;
    p.coef.push_back(1);
    while (true) {
        p = p * readnum();
        if (nxt >= raw.size() || raw[nxt] != '*') break;
        nxt += 1;
    }
    return p;
}

Poly readadd() {
    Poly p;
    bool neg = false;
    while (true) {
        Poly sub = readmul();
        if (neg) sub = -sub;
        p = p + sub;
        if (nxt >= raw.size() || (raw[nxt] != '+' && raw[nxt] != '=')) break;
        neg |= (raw[nxt] == '=');
        nxt += 1;
    }
    return p;
}

vector<pair<ll, int>> factorize(ll x) {
    vector<pair<ll, int>> facts;
    ll i = 2;
    while (x > 1) {
        if (i * i > x) {
            facts.push_back({x, 1});
            break;
        }
        int n = 0;
        while (x % i == 0) x /= i, n++;
        if (n > 0) facts.push_back({i, n});
        i += 1;
    }
    return facts;
}

void testcase() {
    nxt = 0, hidigit = 1;
    poly = readadd().coef;

    // cerr << "got polynomial ";
    // rep(i, poly.size()) cerr << poly[i] << "x^" << i
    //                         << (i == poly.size() - 1 ? "" : " + ");
    // cerr << " = 0" << endl;

    while (poly.size() && poly.back() == 0) poly.pop_back();
    while (poly.size() && poly.front() == 0) poly.erase(poly.begin());
    if (poly.empty()) {
        cout << hidigit + 1 << "+\n";
        return;
    }

    // cerr << "got reduced polynomial ";
    // rep(i, poly.size()) cerr << poly[i] << "x^" << i
    //                         << (i == poly.size() - 1 ? "" : " + ");
    // cerr << " = 0" << endl;

    vector<pair<ll, int>> facts = factorize(abs(poly.front()));

    // cerr << "got factors of " << poly.front() << ":";
    // for (auto& f : facts) cerr << " " << f.first << " (x" << f.second << ")";
    // cerr << endl;

    vector<int> f(facts.size());
    vector<ll> roots;
    while (true) {
        ll num = 1;
        rep(i, f.size()) rep(j, f[i]) num *= facts[i].first;
        bigint x = num;

        bigint y;
        bigint xpow = 1;
        for (ll c : poly) {
            bigint b = c;
            b *= xpow;
            y += b;
            xpow *= x;
        }
        // cerr << "P(" << num << ") = " << out << endl;
        if (y == 0 && num > hidigit) roots.push_back(num);

        int i = 0;
        while (i < f.size()) {
            f[i] += 1;
            if (f[i] > facts[i].second)
                f[i++] = 0;
            else
                break;
        }
        if (i == f.size()) break;
    }
    sort(roots.begin(), roots.end());
    rep(i, roots.size()) cout << roots[i] << " \n"[i == roots.size() - 1];
    if (roots.empty()) cout << "*\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> raw) {
        if (raw == "=") break;
        testcase();
    }
}
