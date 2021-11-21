
#include "../common.h"

#define NOMAIN_MOD
#include "mod.cpp"

using cd = complex<double>;
const double PI = acos(-1);

// compute the DFT of a power-of-two-length sequence.
// if `inv` is true, computes the inverse DFT.
//
// the DFT of a polynomial A(x) = A0 + A1*x + A2*x^2 + ... + An*x^n is the array
// of the polynomial A evaluated in all nths roots of unity: [A(w0), A(w1),
// A(w2), ..., A(wn-1)], where w0 = 1 and w1 is the nth principal root of unity.
void fft(vector<cd>& a, bool inv) {
    int N = a.size();
    assert(N == 1 << __builtin_ctz(N));

    int k = 0;
    rep(i, N) {
        int bit = N >> 1;
        while (k & bit) k ^= bit, bit >>= 1;
        k ^= bit;
        if (i < k) swap(a[i], a[k]);
    }

    for (int len = 2; len <= N; len <<= 1) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < N; i += len) {
            cd w(1);
            rep(j, 0, len / 2) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
            i += len;
        }
        len <<= 1;
    }

    if (inv)
        for (cd& x : a) x /= N;
}

const ll MOD = 7340033, ROOT = 5, ROOTPOW = 1 << 20;

// compute the DFT of a power-of-two-length sequence, modulo a special prime
// number with principal root.
//
// the modulus _must_ be a prime number with an Nth root of unity, where N is a
// power of two. the FFT can only be performed on arrays of size <= N.
void modfft(vector<ll>& a, bool inv) {
    int N = a.size();
    assert(N == 1 << __builtin_ctz(N) && N <= ROOTPOW);
    rep(i, N) a[i] = (a[i] % MOD + MOD) % MOD;

    int k = 0;
    rep(i, 1, N) {
        int bit = N >> 1;
        while (k & bit) k ^= bit, bit >>= 1;
        k ^= bit;
        if (i < k) swap(a[i], a[k]);
    }

    for (int len = 2; len <= N; len <<= 1) {
        ll wlen = inv ? multinv(ROOT, MOD) : ROOT;
        for (ll i = ROOTPOW; i > len; i >>= 1) wlen = wlen * wlen % MOD;
        for (int i = 0; i < N; i += len) {
            ll w = 1;
            rep(j, 0, len / 2) {
                ll u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }

    if (inv) {
        ll ninv = multinv(N, MOD);
        for (ll& x : a) x = x * ninv % MOD;
    }
}

using T = ll;
T pmul(T a, T b) { return a * b % MOD; }
T padd(T a, T b) { return (a + b) % MOD; }
T psub(T a, T b) { return (a - b + MOD) % MOD; }
T pinv(T a) { return multinv(a, MOD); }

struct Poly {
    vector<T> a;

    Poly() {}
    Poly(T c) : a(c) { trim(); }
    Poly(vector<T> c) : a(c) { trim(); }

    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }
    int deg() const { return a.empty() ? -1000000 : a.size() - 1; }
    Poly sub(int l, int r) const {
        r = min(r, (int)a.size()), l = min(l, r);
        return vector<T>(a.begin() + l, a.begin() + r);
    }
    Poly trunc(int n) const { return sub(0, n); }
    Poly shl(int n) const {
        Poly out = *this;
        out.a.insert(out.a.begin(), n, 0);
        return out;
    }
    Poly rev(int n, bool r = false) const {
        Poly out(*this);
        if (r) out.a.resize(max(n, (int)a.size()));
        reverse(out.a.begin(), out.a.end());
        return out.trunc(n);
    }

    Poly& operator+=(const Poly& rhs) {
        auto& b = rhs.a;
        a.resize(max(a.size(), b.size()));
        rep(i, b.size()) a[i] = padd(a[i], b[i]);  // add
        trim();
        return *this;
    }
    Poly& operator-=(const Poly& rhs) {
        auto& b = rhs.a;
        a.resize(max(a.size(), b.size()));
        rep(i, b.size()) a[i] = psub(a[i], b[i]);  // sub
        trim();
        return *this;
    }
    Poly& operator*=(const Poly& rhs) {
        int n = deg() + rhs.deg() + 1;
        if (n <= 0) return *this = Poly();
        n = 1 << (n <= 1 ? 0 : 32 - __builtin_clz(n - 1));
        vector<T> b = rhs.a;
        a.resize(n), b.resize(n);
        modfft(a, false), modfft(b, false);        // fft
        rep(i, a.size()) a[i] = pmul(a[i], b[i]);  // mul
        modfft(a, true), trim();                   // invfft
        return *this;
    }
    Poly inv(int n) const {
        assert(deg() >= 0);
        Poly ans = pinv(a[0]);  // inverse
        int b = 1;
        while (b < n) {
            Poly C = (ans * trunc(2 * b)).sub(b, 2 * b);
            ans -= (ans * C).trunc(b).shl(b);
            b *= 2;
        }
        return ans.trunc(n);
    }

    Poly operator+(const Poly& rhs) const { return Poly(*this) += rhs; }
    Poly operator-(const Poly& rhs) const { return Poly(*this) -= rhs; }
    Poly operator*(const Poly& rhs) const { return Poly(*this) *= rhs; }

    pair<Poly, Poly> divmod(const Poly& b) const {
        if (deg() < b.deg()) return {Poly(), *this};
        int d = deg() - b.deg() + 1;
        Poly D = (rev(d) * b.rev(d).inv(d)).trunc(d).rev(d, true);
        return {D, *this - D * b};
    }
    Poly operator/(const Poly& b) const { return divmod(b).first; }
    Poly operator%(const Poly& b) const { return divmod(b).second; }
    Poly& operator/=(const Poly& b) { return *this = divmod(b).first; }
    Poly& operator%=(const Poly& b) { return *this = divmod(b).second; }

    T eval(T x) {
        T y = 0;
        invrep(i, a.size()) y = padd(pmul(y, x), a[i]);  // add, mul
        return y;
    }
    Poly& build(vector<Poly>& tree, vector<T>& x, int v, int l, int r) {
        if (l == r) return tree[v] = vector<T>{-x[l], 1};
        int m = (l + r) / 2;
        return tree[v] = build(tree, x, 2 * v, l, m) *
                         build(tree, x, 2 * v + 1, m + 1, r);
    }
    void subeval(vector<Poly>& tree, vector<T>& x, vector<T>& y, int v, int l,
                 int r) {
        if (l == r) {
            y[l] = eval(x[l]);
            return;
        }
        int m = (l + r) / 2;
        (*this % tree[2 * v]).subeval(tree, x, y, 2 * v, l, m);
        (*this % tree[2 * v + 1]).subeval(tree, x, y, 2 * v + 1, m + 1, r);
    }
    // evaluate m points in O(k (log k)^2) with k = max(n, m).
    vector<T> multieval(vector<T>& x) {
        int N = x.size();
        if (deg() < 0) return vector<T>(N, 0);
        vector<Poly> tree(4 * N);
        build(tree, x, 1, 0, N - 1);
        vector<T> y(N);
        subeval(tree, x, y, 1, 0, N - 1);
        return y;
    }

    friend ostream& operator<<(ostream& s, const Poly& p) {
        s << "(";
        bool first = true;
        rep(i, p.a.size()) {
            if (p.a[i] == 0) continue;
            if (!first) s << " + ";
            s << p.a[i];
            if (i > 0) s << " x";
            if (i > 1) s << "^" << i;
            first = false;
        }
        s << ")";
        return s;
    }
};

#ifndef NOMAIN_POLY

int main() {
    Poly p1({1, 4});
    Poly p2({-3, 2});
    Poly p3({12, 12, 12, 1});
    Poly p4({128, 40, 29, 2, 0});

    cout << p1 << " * " << p2 << " = " << p1 * p2 << endl;

    vector<ll> xs = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    for (ll& x : xs) x = (x % MOD + MOD) % MOD;
    vector<ll> ys = p2.multieval(xs);
    cout << "P(x) = " << p2 << endl;
    cout << "x -> P(x):" << endl;
    rep(i, xs.size()) { cout << "  " << xs[i] << " -> " << ys[i] << endl; }
}

#endif
