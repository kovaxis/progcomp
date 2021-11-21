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

vector<int> adj[2][1001];
int comp[2][1001];
int nextcomp[2];
bool pairs[2][1001][1001];

pair<int, int> subsets[2][1001];

int find(pair<int, int> subsets[], int i) {
    if (subsets[i].first != i)
        subsets[i].first = find(subsets, subsets[i].first);
    return subsets[i].first;
}

void unite(pair<int, int> subsets[], int i, int j) {
    if (subsets[i].second > subsets[j].second) {
        subsets[j].first = i;
    } else if (subsets[i].second < subsets[j].second) {
        subsets[i].first = j;
    } else {
        subsets[i].first = j;
        subsets[j].second += 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M[2];
    cin >> N >> M[0] >> M[1];
    rep(j, 2) rep(i, N) { subsets[j][i] = {i, 0}; }
    rep(j, 2) rep(i, M[j]) {
        int u, v;
        cin >> u >> v;
        u -= 1;
        v -= 1;
        unite(subsets[j], find(subsets[j], u), find(subsets[j], v));
    }

    vector<pair<int, int>> edges;
    rep(u, N) rep(v, u + 1, N) {
        int i[2] = {find(subsets[0], u), find(subsets[1], u)};
        int j[2] = {find(subsets[0], v), find(subsets[1], v)};
        if (i[0] == j[0] || i[1] == j[1]) continue;
        edges.push_back({u, v});
        rep(m, 2) unite(subsets[m], i[m], j[m]);
    }
    cout << edges.size() << '\n';
    for (auto edge : edges) {
        cout << edge.first + 1 << " " << edge.second + 1 << '\n';
    }
}
