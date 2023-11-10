#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define LOG2(X) ((unsigned)(8 * sizeof(unsigned long long) - __builtin_clzll((X)) - 1))
#define MOD 998244353
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

struct Vertex {
    int next[26], go[26];
    int p, link = -1, exit = -1, cnt = -1;
    vector<int> leaf;
    char pch;
    Vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
        rep(i, 26) next[i] = -1, go[i] = -1;
    }
};
vector<Vertex> t(1);
void add(string &s, int id) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].leaf.push_back(id);
}
int go(int v, char ch);
int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0) t[v].link = 0;
        else t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}
int go(int v, char ch) {
    int c = ch - 'a';
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1) t[v].go[c] = t[v].next[c];
        else t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
}
int next_match(int v) { // Optional
    if (t[v].exit == -1) {
        if (t[get_link(v)].leaf.size()) t[v].exit = get_link(v);
        else t[v].exit = v == 0 ? 0 : next_match(get_link(v));
    }
    return t[v].exit;
}
int cnt_matches(int v) { // Optional
    if (t[v].cnt == -1)
        t[v].cnt = v == 0 ? 0 : t[v].leaf.size() + cnt_matches(get_link(v));
    return t[v].cnt;
}

ll pow2(ll e) {
    ll ans = 1;
    rep(i, e) ans = (ans * 2) % MOD;
    return ans;
}

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

Poly LinearRec(Poly trans, ll k) {
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

vector<ModInt> Power(vector<vector<pair<ll, int>>> G, ll k, vector<ModInt> v) {
    int n = G.size();
    vector<Poly> first(2 * n, Poly(n));
    first[0] = v;
    vector<ModInt> s(2 * n);
    s[0] = v[0];

    // Step 1 (optimizable to O(m * n))
    for (int i = 1; i < 2 * n; ++i) {
        for (int from = 0; from < n; ++from)
            for (auto [w, to] : G[from])
                first[i][from] = first[i][from] + ModInt(w) * first[i - 1][to];
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;
    cin >> n >> m;
    vector<string> s(m);
    rep(i, m) cin >> s[i];

    rep(i, m) add(s[i], i);

    int nodes = t.size();
    vector<vector<pair<ll, int>>> graph(nodes);
    rep(i, nodes) {
        repx(c, 'a', 'z' + 1) {
            int next = go(i, c);
            ll pond = pow2(cnt_matches(next));
            // cerr << "edge '" << (char)c << "' from " << i << " to " << next << " with pond = " << pond << endl;
            graph[i].push_back({pond, next});
        }
    }

    Poly v(graph.size(), 1);

    Poly ans_vec = Power(graph, n, v);

    cout << ans_vec[0].x << endl;
}
