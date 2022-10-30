
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)
#define repx(i, a, n) for (int i = a; i < n; i++)

struct Dsu {
    vector<int> p, r;

    Dsu() {}
    // initialize the disjoint-set-union to all unitary sets
    void reset(int N) {
        p.resize(N), r.assign(N, 0);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two disjoint sets with leaders `i` and `j`
    // note: `i` and `j` must be LEADERS
    int unite(int i, int j) {
        if (i == j) return i;
        if (r[i] > r[j]) {
            p[j] = i;
            return j;
        } else {
            if (r[i] == r[j]) r[j] += 1;
            p[i] = j;
            return i;
        }
    }
};

int N, M;
vector<pair<int, pair<int, int>>> edges;
vector<int> ans;
Dsu bip;

bool caninclude(int b, int e) {
    map<int, int> seen;
    int edgn = 0;
    repx(i, b, e) {
        int x = edges[i].second.first, y = edges[i].second.second;
        int u = bip.find(x), v = bip.find(y);
        if (v == bip.find(x + N) || u == bip.find(y + N)) continue;
        seen[u] += 1, seen[v] += 1;
        if (u == v) seen[u] -= 1;
        edgn += 1;
    }

    if (seen.size() == 0) return false;
    for (auto p : seen)
        if (p.second == edgn) return false;

    bool istri = (seen.size() == 3);
    repx(i, b, e) {
        int u = bip.find(edges[i].second.first),
            v = bip.find(edges[i].second.second);
        if (u == v) istri = false;
    }

    return !istri;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    rep(i, M) {
        int u, v, b;
        cin >> u >> v >> b;
        edges.push_back({-b, {u - 1, v - 1}});
    }

    sort(edges.begin(), edges.end());
    bip.reset(2 * N);

    int j = 0;
    while (j < M) {
        int b = -edges[j].first;
        int i = j;
        while (j < M && -edges[j].first == b) j++;

        // check if edges can be included
        // cerr << "can_include(" << b << ") = " << caninclude(i, j) << endl;
        if (caninclude(i, j)) ans.push_back(b);

        // check if edges can be excluded
        bool ok = true;
        repx(k, i, j) {
            int u = edges[k].second.first;
            int v = edges[k].second.second;
            bip.unite(bip.find(u), bip.find(v + N));
            bip.unite(bip.find(u + N), bip.find(v));
            if (bip.find(u) == bip.find(u + N)) ok = false;
            if (bip.find(v) == bip.find(v + N)) ok = false;
        }
        // cerr << "can_exclude(" << b << ") = " << ok << endl;
        if (!ok) break;

        if (j >= M) ans.push_back(0);
    }

    if (ans.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        rep(i, ans.size()) cout << ans[ans.size() - i - 1] << "\n";
    }
}