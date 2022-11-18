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

const ll M = 998244353;

// binary exponentiation modulo M.
ll binexp(ll a, ll m) {
    assert(m >= 0);
    ll res = 1 % M;
    while (m) {
        if (m & 1) res = (res * a) % M;
        a = (a * a) % M;
        m >>= 1;
    }
    return res;
}

// compute the modular multiplicative inverse, assuming M is prime.
ll multinv(ll a) { return binexp(a, M - 2); }

map<ll, int> factorize(ll x) {
    map<ll, int> facts;
    ll k = 2;
    while (x > 1) {
        if (k * k > x) {
            facts.insert({x, 1});
            break;
        }
        int n = 0;
        while (x % k == 0) x /= k, n++;
        if (n > 0) facts.insert({k, n});
        k += 1;
    }
    return facts;
}

void mcm(map<ll, int>& lhs, map<ll, int>& rhs) {
    if (lhs.size() < rhs.size()) swap(lhs, rhs);
    for (auto p : rhs) {
        lhs[p.first] = max(lhs[p.first], p.second);
    }
}

void mul(map<ll, int>& lhs, const map<ll, int>& rhs) {
    for (auto p : rhs) {
        lhs[p.first] += p.second;
    }
}

void reduce(map<ll, int>& lhs, const map<ll, int>& rhs) {
    for (auto p : rhs) {
        lhs[p.first] = max(lhs[p.first] - p.second, 0);
    }
}

int N;
vector<vector<pair<int, pair<ll, ll>>>> G;
ll ans;

map<ll, int> dfs(int u, int p) {
    map<ll, int> f;
    for (auto c : G[u]) {
        if (c.first == p) continue;
        map<ll, int> sub = dfs(c.first, u);
        mul(sub, factorize(c.second.first));
        reduce(sub, factorize(c.second.second));
        mcm(f, sub);
    }
    return f;
}

void ans_dfs(int u, ll scale, int p) {
    // cerr << "assigning " << scale << " to ingredient " << u + 1 << endl;
    ans += scale;
    ans %= M;
    for (auto c : G[u]) {
        if (c.first == p) continue;
        ll sub = scale * multinv(c.second.first) % M * c.second.second % M;
        ans_dfs(c.first, sub, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        G.assign(N, vector<pair<int, pair<ll, ll>>>());
        rep(k, N - 1) {
            ll i, j, x, y;
            cin >> i >> j >> x >> y;
            i -= 1;
            j -= 1;

            G[i].push_back({j, {x, y}});
            G[j].push_back({i, {y, x}});
        }

        map<ll, int> f = dfs(0, 0);
        ll scale = 1;
        for (auto p : f) {
            scale *= binexp(p.first, p.second);
            scale %= M;
        }

        ans = 0;
        ans_dfs(0, scale, 0);
        cout << ans << "\n";
    }
}
