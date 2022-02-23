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

// hackproof unordered map hash
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

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

inline int nextbit(int n) { return n == 0 ? 0 : 32 - __builtin_clz(n); }

const ll MOD = 1e9 + 7;

ll binexp(ll a, ll m, ll M = MOD) {
    assert(m >= 0);
    ll res = 1 % M;
    while (m) {
        if (m & 1) res = (res * a) % M;
        a = (a * a) % M;
        m >>= 1;
    }
    return res;
}

ll A, N;
umap<int, ll> discount;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> A >> N;
    rep(i, N) {
        ll v;
        cin >> v;
        ll sub = (binexp(2, A - nextbit((int)v)) - discount[v] + MOD) % MOD;
        cout << sub << "\n";

        ll last = -1;
        for (ll mask = 0; mask <= (ll)INT32_MAX; mask = (mask << 1) | 1) {
            ll u = v & mask;
            if (u == last) continue;
            discount[u] = (discount[u] + sub) % MOD;
            last = u;
        }
    }
}
