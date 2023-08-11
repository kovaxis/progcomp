#pragma GCC optimize("Ofast")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

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
// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

int N, M;
vector<vector<int>> G;
uset<int> bad;
vector<int> badcnt;
vector<bool> color;

void recompute(int u) {
    int newcnt = 0;
    for (int v : G[u])
        if (color[v] == color[u]) newcnt += 1;
    if (badcnt[u] <= 1 && newcnt > 1) bad.insert(u);
    else if (badcnt[u] > 1 && newcnt <= 1) bad.erase(u);
    badcnt[u] = newcnt;
}

void update(int u, int c) {
    if (c == color[u]) return;
    color[u] = c;
    recompute(u);
    for (int v : G[u]) {
        badcnt[v] += (c == color[v] ? 1 : -1);
        if (badcnt[v] == 2) bad.insert(v);
        else if (badcnt[v] == 1) bad.erase(v);
    }
}

int main() {
    cin >> N >> M;
    G.resize(N);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    color.resize(N), badcnt.resize(N);
    rep(u, N) recompute(u);

    while (!bad.empty()) {
        int u = *bad.begin();
        update(u, !color[u]);
    }

    rep(u, N) cout << "01"[color[u]];
    cout << endl;
}
