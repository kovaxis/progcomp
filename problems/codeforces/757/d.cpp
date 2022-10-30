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

// factor, next
umap<int, pair<int, int>> factdp;
pair<int, int> getfact(int x, int k = 2) {
    if (factdp.count(x)) return factdp[x];
    while (k * k <= x) {
        if (x % k == 0) {
            getfact(x / k, k);
            return factdp[x] = {k, x / k};
        }
        k += 1;
    }
    return factdp[x] = {x, 1};
}

void factorize(vector<pair<int, int>>& fact, int x) {
    while (true) {
        pair<int, int> f = getfact(x);
        if (f.first == 1) break;
        if (!fact.empty() && fact.back().first == f.first)
            fact.back().second += 1;
        else
            fact.push_back({f.first, 1});
        x = f.second;
    }
}

template <class OP>
void divisors(ll x, OP op) {
    vector<pair<int, int>> facts;
    factorize(facts, x);
    vector<int> f(facts.size());
    while (true) {
        int y = 1;
        rep(i, f.size()) rep(j, f[i]) y *= facts[i].first;
        op(y);

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
}

int N;
umap<int, int> a;
vector<int> aorder;
umap<int, ll> dp;
umap<int, int> mults;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, N) {
        int x;
        cin >> x;
        a[x] += 1;
    }

    for (auto x : a) aorder.push_back(x.first);
    sort(aorder.begin(), aorder.end());
    for (auto x : a) divisors(x.first, [&](int d) { mults[d] += x.second; });
    for (int x : aorder) {
        ll mx = 0;
        divisors(x, [&](int d) {
            if (!a.count(d)) return;
            ll sub = dp[d] - (ll)(d - 1) * mults[x];
            mx = max(mx, sub);
        });
        mx += (ll)(x - 1) * mults[x];
        dp[x] = mx;
        cerr << "dp[" << x << "] = " << mx << endl;
    }

    ll ans = 0;
    for (auto x : dp) ans = max(ans, x.second);

    ans += N;
    cout << ans << "\n";
}
