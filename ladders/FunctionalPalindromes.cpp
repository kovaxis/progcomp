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

template <class T>
struct Sparse {
    vector<vector<T>> st;

    Sparse() {}

    void resize(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }
    // O(N log N) time
    // O(N log N) memory
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        rep(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));  // query op
    }

    // query maximum in the range [l, r) in O(1) time
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return max(st[i][l], st[i][r - (1 << i)]);  // query op
    }
};

void manacher(const string& s, vector<int>& p) {
    int N = s.size(), P = 2 * N - 1;
    p.assign(P, 0);
    int l = 0, r = -1;
    rep(i, P) {
        int d = (r >= i ? min(p[l + r - i], r - i + 2) : i % 2);
        while (i - d >= 0 && i + d < P && s[(i - d) / 2] == s[(i + d) / 2])
            d += 2;
        p[i] = d;
        if (i + d - 2 > r) l = i - d + 2, r = i + d - 2;
    }
    rep(i, P) p[i] -= 1;
}

vector<int> suffixarray(const string& s) {
    int N = s.size() + 1;  // include terminating NUL
    vector<int> p(N), p2(N), c(N), c2(N), cnt(256);
    rep(i, N) cnt[s[i]] += 1;
    rep(b, 1, 256) cnt[b] += cnt[b - 1];
    rep(i, N) p[--cnt[s[i]]] = i;
    rep(i, 1, N) c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    for (int k = 1; k < N; k <<= 1) {
        int C = c[p[N - 1]] + 1;
        cnt.assign(C + 1, 0);
        for (int& pi : p) pi = (pi - k + N) % N;
        for (int cl : c) cnt[cl + 1] += 1;
        rep(i, C) cnt[i + 1] += cnt[i];
        rep(i, N) p2[cnt[c[p[i]]]++] = p[i];
        c2[p2[0]] = 0;
        rep(i, 1, N) c2[p2[i]] =
            c2[p2[i - 1]] + (c[p2[i]] != c[p2[i - 1]] ||
                             c[(p2[i] + k) % N] != c[(p2[i - 1] + k) % N]);
        swap(c, c2), swap(p, p2);
    }
    p.erase(p.begin());  // erase terminating NUL
    return p;
}

const ll A = 100001, MOD = 1000000007;
vector<ll> apow;

template <class T>
struct St {
    vector<T> node;

    St() {}
    void resize(int N) { node.resize(4 * N); }

    void build(const string& s, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * s.size());
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            node[v] = s[vl];  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(s, 2 * v, vl, vm);
        build(s, 2 * v + 1, vm + 1, vr);
        node[v] = (node[2 * v] * apow[vr - vm] % MOD + node[2 * v + 1]) %
                  MOD;  // query op
    }

    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = 0;  // neutral element
        if (l <= vm)
            val = query(l, min(r, vm), 2 * v, vl, vm) * apow[max(r - vm, 0)] %
                  MOD;  // query op
        if (r >= vm + 1)
            val = (val + query(max(l, vm + 1), r, 2 * v + 1, vm + 1, vr)) %
                  MOD;  // query op
        return val;
    }
};

vector<int> makelcp(const string& s, const vector<int>& p) {
    int N = p.size(), k = 0;
    vector<int> r(N), lcp(N);
    rep(i, N) r[p[i]] = i;
    rep(i, N) {
        if (r[i] + 1 >= N) {
            k = 0;
            continue;
        }
        int j = p[r[i] + 1];
        while (i + k < N && j + k < N && s[i + k] == s[j + k]) k += 1;
        lcp[r[i]] = k;
        if (k) k -= 1;
    }
    return lcp;
}

int N, Q, P;
string s;
vector<int> ps, sa, lcp;
Sparse<int> nxt, lcpq;
St<ll> ftab;

// get the ending position of next palindrome that starts at `i`, searching from
// `j`. (all string pos). if no such palindrome exists, returns `N`.
//
// O(log N)
int get_next(int i, int j) {
    j = i + j, i = 2 * i;
    int l = j, r = P;
    while (l != r) {
        int m = l + (r - l) / 2;
        if (nxt.query(j, m + 1) < -i) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return min((2 * l - i) / 2, N);
}

// find the last index after `i` with lcp(i, j) >= cutoff.
int lcpsearch(int i, int cutoff) {
    int l = i + 1, r = N;
    while (l != r) {
        int m = l + (r - l) / 2;
        if (-lcpq.query(i, m) >= cutoff) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    s.reserve(N);
    cin >> s;
    N = s.size();

    apow.resize(N);
    apow[0] = 1;
    rep(i, 1, N) apow[i] = apow[i - 1] * A % MOD;
    ftab.build(s);

    manacher(s, ps);
    P = ps.size();
    sa = suffixarray(s), lcp = makelcp(s, sa);

    nxt.resize(P);
    rep(i, P) nxt.set(i, ps[i] - i - 1);
    nxt.init();

    lcpq.resize(N);
    rep(i, N) lcpq.set(i, -lcp[i]);
    lcpq.init();

    vector<pair<ll, pair<int, int>>> palis;
    ll palicount = 0;
    int k = 0;
    rep(i, N) {
        while (true) {
            int nx = get_next(sa[i], sa[i] + k);
            if (nx == N) break;
            k = nx - sa[i] + 1;
            int j = lcpsearch(i, k);
            palicount += j - i + 1;
            palis.push_back({palicount, {sa[i], nx}});
        }
        k = min(k, lcp[i]);
    }

    rep(q, Q) {
        ll k;
        cin >> k;

        int l = 0, r = palis.size();
        while (l != r) {
            int m = l + (r - l) / 2;
            if (palis[m].first < k) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        if (l == palis.size()) {
            cout << "-1\n";
        } else {
            auto& p = palis[l].second;
            cout << ftab.query(p.first, p.second) << "\n";
        }
    }
}
