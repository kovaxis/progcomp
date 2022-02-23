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
using umap = unordered_map<T, U>;

int N, E;
ll K;
umap<string, int> attrmap;
vector<ll> attrs;
vector<pair<int, ll>> evs;

vector<ll> needs;
vector<ll> attrevs;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string tmps;

    cin >> N >> K;
    attrs.resize(N);
    rep(i, N) {
        cin >> tmps >> attrs[i];
        attrmap[tmps] = i;
    }
    cin >> E;
    evs.resize(E);
    rep(e, E) {
        cin >> tmps >> evs[e].second;
        evs[e].first = attrmap[tmps];
    }

    needs.resize(N);
    rep(e, E) {
        auto& ev = evs[e];
        auto& i = ev.first;
        needs[i] = max(needs[i], ev.second - attrs[i]);
    }
    rep(i, N) K -= needs[i];
    if (K < 0) {
        cout << "0\n";
        return 0;
    }

    ll ans = 0;
    rep(e, E) ans += attrs[evs[e].first] + needs[evs[e].first] - evs[e].second;

    attrevs.resize(N);
    rep(e, E) attrevs[evs[e].first] += 1;
    ll maxevs = 0;
    rep(i, N) maxevs = max(maxevs, attrevs[i]);
    ans += maxevs * K;

    cout << ans << "\n";
}
