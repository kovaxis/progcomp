#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll &x) const {
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

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

ll P[2];
ll T[2];
ll H, S;

vector<pair<umap<ll, ll>, umap<ll, ll>>> dpmem;

ll dp(ll h, ll r0, ll r1) {
    // cout << "calculating dp(" << h << ", " << r0 << ", " << r1 << ")" << endl;
    if (h <= 0) return 0;
    ll *cache;
    if (r0 == T[0]) {
        if (dpmem[h].first.count(r1)) return dpmem[h].first[r1];
        cache = &dpmem[h].first[r1];
    } else if (r1 == T[1]) {
        if (dpmem[h].second.count(r0)) return dpmem[h].second[r0];
        cache = &dpmem[h].second[r0];
    } else {
        throw "unreachable";
    }

    ll ans = 1e18;
    // fire laser 0
    if (r1 - r0 >= 0) ans = min(ans, dp(h - (P[0] - S), T[0], r1 - r0) + r0);
    // fire laser 1
    if (r0 - r1 >= 0) ans = min(ans, dp(h - (P[1] - S), r0 - r1, T[1]) + r1);
    // fire both lasers
    ans = min(ans, dp(h - (P[0] + P[1] - S), T[0], T[1]) + max(r0, r1));

    return *cache = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    rep(k, 2) cin >> P[k] >> T[k];
    cin >> H >> S;

    dpmem.resize(H + 1);
    cout << dp(H, T[0], T[1]) << "\n";
}
