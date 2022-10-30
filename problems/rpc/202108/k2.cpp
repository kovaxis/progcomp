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

const ll INF = 1e14;

int N, M;
pair<int, pair<int, int>> edges[500009];
pair<int, int> dsu[100001];

// find the leader node corresponding to node `i`
int find(int i) {
    if (dsu[i].first != i) dsu[i].first = find(dsu[i].first);
    return dsu[i].first;
}

// perform union on the two disjoint sets with leaders `i` and `j`
// note: `i` and `j` must be LEADERS OF TWO SEPARATE SETS
bool unite(int i, int j) {
    if (dsu[i].second > dsu[j].second) {
        dsu[j].first = i;
        return j;
    } else {
        if (dsu[i].second == dsu[j].second) dsu[j].second += 1;
        dsu[i].first = j;
        return i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    rep(m, M) {
        int u, v, t;
        cin >> u >> v >> t;
        edges[m] = {t, {u - 1, v - 1}};
    }
    sort(edges, edges + M);

    rep(i, N) dsu[i] = {i, 0};

    int ecount = 0;
    ll cost = 0;
    rep(m, M) {
        if (ecount >= N - 1) break;
        auto& e = edges[m];
        int u = find(e.second.first), v = find(e.second.second);
        if (u != v) {
            unite(u, v);
            cost += e.first;
            ecount += 1;
        }
    }

    cout << cost << endl;
}
