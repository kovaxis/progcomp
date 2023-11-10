#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

struct ModInt {
    int x;
    ModInt(int x = 0) : x(x + (x < 0) * MOD - (x >= MOD) * MOD) {}
    ModInt operator+(ModInt o) { return x + o.x; }
    ModInt operator-(ModInt o) { return x - o.x; }
    ModInt operator*(ModInt o) { return 1LL * x * o.x % MOD; }
    ModInt operator/(ModInt b) { return *this * b.inv(); }
    ModInt inv() { return pow(MOD - 2); }
    ModInt pow(long long e) {
        if (!e) return ModInt(1);
        ModInt r = pow(e / 2);
        r = r * r;
        return e % 2 ? *this * r : r;
    }
    bool operator==(ModInt o) { return x == o.x; }
};

vector<ModInt> BerlekampMassey(vector<ModInt> s) {
    int n = s.size();
    vector<ModInt> C(n), B(n);
    C[0] = B[0] = 1;

    auto b = C[0];
    int L = 0;
    for (int i = 0, m = 1; i < n; ++i) {
        /// Calculate discrepancy
        auto d = s[i];
        for (int j = 1; j <= L; ++j)
            d = d + C[j] * s[i - j];
        if (d == 0) {
            ++m;
            continue;
        }
        /// C -= d / b * B * X^m
        auto T = C;
        auto coef = d / b;
        for (int j = m; j < n; ++j)
            C[j] = C[j] - coef * B[j - m];
        if (2 * L > i) {
            ++m;
            continue;
        }
        L = i + 1 - L;
        B = T;
        b = d;
        m = 1;
    }
    C.resize(L + 1);
    C.erase(C.begin());
    for (auto &x : C) x = x * (-1);
    return C;
}

using Poly = vector<ModInt>;

Poly LinearRec(Poly trans, int k) {
    int n = trans.size(); // assert(n <= (int)first.size());
    Poly r(n + 1), b(r);
    r[0] = b[1] = 1;
    auto ans = b[0];

    auto combine = [&](Poly a, Poly b) { // a * b mod trans
        Poly res(n * 2 + 1);
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                res[i + j] = res[i + j] + a[i] * b[j];
        for (int i = 2 * n; i > n; --i)
            for (int j = 0; j < n; ++j)
                res[i - 1 - j] = res[i - 1 - j] + res[i] * trans[j];
        res.resize(n + 1);
        return res;
    };
    // Consider caching the powers for multiple queries
    for (++k; k; k /= 2) {
        if (k % 2) r = combine(r, b);
        b = combine(b, b);
    }
    return r;
}

vector<ModInt> Power(vector<Poly> M, int k, vector<ModInt> v) {
    int n = M.size();
    vector<Poly> first(2 * n, Poly(n));
    first[0] = v;
    vector<ModInt> s(2 * n);
    s[0] = v[0];

    // Step 1 (optimizable to O(m * n))
    for (int i = 1; i < 2 * n; ++i) {
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                first[i][k] = first[i][k] + M[j][k] * first[i - 1][j];
        s[i] = first[i][0];
    }

    // Step 2 (O(n^2))
    auto trans = BerlekampMassey(s);
    int rec = trans.size();

    // Step 3 (O(n^2 log k))
    auto c = LinearRec(trans, k);

    // Step 4 (O(n^2))
    vector<ModInt> ans(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < rec; ++j)
            ans[i] = ans[i] + c[j + 1] * first[j][i];

    return ans;
}

int main() {
    int n;
    cin >> n;

    vector<Poly> M(n, Poly(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> M[i][j].x;
    Poly v(n, 1);

    for (int k = 0; k < 100; ++k) {
        cout << endl
             << "k = " << k << endl;
        auto ans = Power(M, k, v);
        for (int i = 0; i < ans.size(); i++)
            cout << ans[i].x << " ";
        cout << endl;
    }

    return 0;
}