#include "../common.h"

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
            repx(i, j, max(ls, rs + j)) {
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

#ifndef NOMAIN_BIGINT

void show(const bigint& a) {
    if (a.neg) {
        bigint b = a;
        b.negate();
        cout << "-{";
        rep(i, b.digits.size()) cout << (i ? ", " : "") << b.digits[i];
        cout << "}";
    } else {
        cout << "+{";
        rep(i, a.digits.size()) cout << (i ? ", " : "") << a.digits[i];
        cout << "}";
    }
}

template <class OP, class ROP>
bigint doop(bigint a, bigint b, bigint ex, const char* opname, OP op,
            ROP revop) {
    bigint out = a;
    op(out, b);
    show(a);
    cout << " " << opname << " ";
    show(b);
    cout << " = ";
    show(out);
    cout << endl;
    if (out != ex) {
        cout << "expected ";
        show(ex);
        cout << ", got ";
        show(out);
        cout << endl;
    }

    bigint outrev = b;
    revop(outrev, a);
    if (outrev != out) {
        cout << "expected ";
        show(out);
        cout << " from reverse op, got ";
        show(outrev);
        cout << endl;
    }

    return out;
}

bigint add(bigint a, bigint b, bigint ex) {
    return doop(
        a, b, ex, "+", [](bigint& a, bigint& b) { a += b; },
        [](bigint& b, bigint& a) { b += a; });
}

bigint sub(bigint a, bigint b, bigint ex) {
    return doop(
        a, b, ex, "-", [](bigint& a, bigint& b) { a -= b; },
        [](bigint& b, bigint& a) {
            b.negate();
            b += a;
        });
}

bigint mul(bigint a, bigint b, bigint ex) {
    return doop(
        a, b, ex, "*", [](bigint& a, bigint& b) { a *= b; },
        [](bigint& b, bigint& a) { b *= a; });
}

bigint div(bigint a, bigint b, bigint exq, bigint exr) {
    bigint outq = a, outr;
    outr = outq.divmod(b);
    show(a);
    cout << " / ";
    show(b);
    cout << " : Q = ";
    show(outq);
    cout << ", R = ";
    show(outr);
    cout << endl;
    if (outq != exq) {
        cout << "expected quotient ";
        show(exq);
        cout << ", got ";
        show(outq);
        cout << endl;
    }
    if (outr != exr) {
        cout << "expected remainder ";
        show(exr);
        cout << ", got ";
        show(outr);
        cout << endl;
    }

    bigint re = outq;
    re *= b, re += outr;
    if (re != a && outr >= bigint() && outr < b) {
        cout << "quotient * rhs + remainder != lhs: expected ";
        show(a);
        cout << ", got ";
        show(re);
        cout << endl;
    }

    return outq;
}

bigint gcd(bigint a, bigint b, bigint ex) {
    bigint k1, k2;
    return doop(
        a, b, ex, "<gcd>",
        [&](bigint& a, bigint& b) {
            bigint d = ext_gcd(a, b, k1, k2);
            bigint d1 = k1, d2 = k2;
            d1 *= a, d2 *= b, d1 += d2;
            if (d1 != d) {
                cout << "x*a + y*b = d is not satisfied:" << endl;
                cout << "a = " << a << ", b = " << b << endl;
                cout << "x = " << k1 << ", y = " << k2 << endl;
                cout << "x*a + y*b = " << d1 << ", expected " << d << endl;
            }
            a = d;
        },
        [&](bigint& b, bigint& a) { b = ext_gcd(a, b, k1, k2); });
}

void testprint(bigint x, string s) {
    stringstream ss;
    ss << x;
    string s2;
    ss >> s2;
    cout << "produced string \"" << s2 << "\"" << endl;
    if (s != s2) {
        cout << "expected " << s << ", got " << s2 << endl;
    }
}

int main() {
    bigint zero;
    bigint one = 1;
    bigint two = 2;
    add(1423, 0, 1423);
    add(1234, 4321, 5555);
    sub(1293, 0, 1293);
    sub(1001, 999, 2);
    bigint at60 = mul(1 << 30, 1 << 30, 1ll << 60);
    bigint at120 = mul(at60, at60, bigint({0, 0, 0, 1 << 24}));
    bigint at30at60 = add(at60, 1ll << 30, (1ll << 30) | (1ll << 60));
    bigint at150at180 =
        mul(at120, at30at60, bigint({0, 0, 0, 0, 1 << 22, 1 << 20}));

    add(84170757, 13263482, 0x5ceba7f);
    add(mul(mul(mul(57168222, 54926541, 0xb27dc7d237046ll),
                mul(32483505, 99223465, 0xb736a7b9d33d9ll),
                bigint({0x9f561d56u, 0x33dc6b7du, 0xbe055109u, 0x7fu})),
            mul(80681649, 9251980, 0x2a6e7ed5604ccll),
            bigint({0xc9f8b888u, 0x06701b48u, 0xd02ee60du, 0xf941a539u,
                    0x152c4fcu})),
        66032065,
        bigint(
            {0xcde84a49u, 0x06701b48u, 0xd02ee60du, 0xf941a539u, 0x152c4fcu}));

    add(3, -2, 1);
    add(-1, 10, 9);
    add(7, -15, -8);
    sub(1, 6, -5);
    sub(6, 3, 3);
    sub(-3, -7, 4);
    sub(-100, 4, -104);
    sub(add(8616485132189ll, -135496843543521ll,
            bigint({0xa2b12c44u, 0x7365u}).negated()),
        sub(-9819684731ll, -435891834565ll, bigint({0x33e10f4au, 0x63u})),
        bigint({0xd6923b8eu, 0x73c8u}).negated());

    mul(0, 1, 0);
    mul(0, 1028472981724ll, 0);
    mul(1, 1, 1);
    mul(1, -1, -1);
    mul(-1, -1, 1);
    mul(-1723872, 0, 0);
    mul(-8, -8, 64);
    mul(8, -8, -64);
    mul(7, 3, 21);
    mul(7, -3, -21);
    mul(-7, 3, -21);
    mul(-7, -3, 21);

    div(1, 1, 1, 0);
    div(1, 2, 0, 1);
    div(153, 1, 153, 0);
    div(234, 100, 2, 34);
    div(0, 100, 0, 0);
    div(1001, 1000, 1, 1);
    div(3873, 4873, 0, 3873);

    div(-1, 1, -1, 0);
    div(1, -1, -1, 0);
    div(-1, -1, 1, 0);
    div(-5, -2, 2, 1);
    div(-9, 2, -4, -1);
    div(101, -3, -33, -2);
    // 1658463516984773554147154214132749 / 65168473546581618593543 =
    // 25448862413 (R = 32587796085235836933490)
    div(bigint({0x5c2e1c0du, 0x16a63331u, 0xc0a3e056u, 0x51c4u}),
        bigint({0xc63a0f07u, 0xca3f653eu, 0xdccu}), bigint({0xecded2cdu, 0x5u}),
        bigint({0x834a5572u, 0x9684e9fau, 0x6e6u}));

    gcd(1, 1, 1);
    gcd(100, 50, 50);
    gcd(91, 21, 7);
    gcd(0, 10, 10);
    gcd(10, 0, 10);
    gcd(bigint({0x4c3cf90cu, 0xad6b1c21u, 0x6ec3925bu, 0xeddb272du, 0x3cf662fdu,
                0x39f83c}),
        bigint({0x4c89c6d9u, 0xa5368789u, 0x93a9c897u, 0x92b679f0, 0xf71b5a14u,
                0x1a6u}),
        811);

    testprint(17298473, "17298473");
    testprint(-0, "0");
    testprint(-129874, "-129874");
    testprint(bigint({0x913cbfb9u, 0xef8d99a2u, 0x131u}),
              "5643518564351694651321");
    testprint(
        bigint({0x13121c04u, 0x44b1fc6au, 0x2dda4fb5u, 0x47cced36u, 0x132c2cu})
            .negated(),
        "-427562167216451295291743197195741678617631748");
}

#endif
