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

pair<int, int> dsu[2][100001];
int prv[2][100005];
int nxt[2][100005];

int find(pair<int, int> dsu[], int i) {
    if (dsu[i].first != i) dsu[i].first = find(dsu, dsu[i].first);
    return dsu[i].first;
}

bool unite(pair<int, int> dsu[], int i, int j) {
    if (dsu[i].second > dsu[j].second) {
        dsu[j].first = i;
        return j;
    } else if (dsu[i].second < dsu[j].second) {
        dsu[i].first = j;
        return i;
    } else {
        dsu[i].first = j;
        dsu[j].second += 1;
        return i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M[2];
    cin >> N >> M[0] >> M[1];
    rep(j, 2) {
        nxt[j][0] = 1;
        rep(i, N) {
            dsu[j][i] = {i, 0};
            prv[j][i + 1] = i;
            nxt[j][i + 1] = i + 2;
        }
    }
    rep(j, 2) rep(i, M[j]) {
        int u, v;
        cin >> u >> v;
        u -= 1;
        v -= 1;
        int rem = unite(dsu[j], find(dsu[j], u), find(dsu[j], v)) + 1;
        nxt[j][prv[j][rem]] = nxt[j][rem];
        prv[j][nxt[j][rem]] = prv[j][rem];
    }

    vector<pair<int, int>> edges;
    int u = nxt[0][0];
    while (u <= N) {
        int v = nxt[1][find(dsu[1], u - 1) + 1];
        while (v <= N) {
            int i[2] = {find(dsu[0], u - 1), find(dsu[1], u - 1)};
            int j[2] = {find(dsu[0], v - 1), find(dsu[1], v - 1)};
            if (!(i[0] == j[0] || i[1] == j[1])) {
                edges.push_back({u, v});
                rep(m, 2) {
                    int rem = unite(dsu[m], i[m], j[m]) + 1;
                    nxt[m][prv[m][rem]] = nxt[m][rem];
                    prv[m][nxt[m][rem]] = prv[m][rem];
                }
                if (prv[0][nxt[0][u]] != u) break;
            }
            v = nxt[1][v];
        }
        u = nxt[0][u];
    }
    /*
    rep(u, N) rep(v, u + 1, N) {
        int i[2] = {find(dsu[0], u), find(dsu[1], u)};
        int j[2] = {find(dsu[0], v), find(dsu[1], v)};
        if (i[0] == j[0] || i[1] == j[1]) continue;
        edges.push_back({u, v});
        rep(m, 2) {
            int rem = unite(dsu[m], i[m], j[m]) + 1;
            nxt[j][prv[j][rem]] = nxt[rem];
            prv[j][nxt[j][rem]] = prv[rem];
        }
    }
    */
    cout << edges.size() << '\n';
    for (auto edge : edges) {
        cout << edge.first << " " << edge.second << '\n';
    }
}
