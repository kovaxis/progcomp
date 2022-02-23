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

int N, base;
vector<vector<int>> G;
vector<int> P;
vector<pair<int, int>> edges;
vector<bool> touched;

void tour(int i) {
    for (int c : G[i]) {
        if (c == P[i]) continue;
        edges.push_back({i, c});
        P[c] = i;
        tour(c);
        edges.push_back({c, i});
    }
}

int ask() {
    int n = 0, x;
    rep(i, N) n += touched[i];
    cout << "? " << n;
    rep(i, N) if (touched[i]) cout << " " << i + 1;
    cout << endl;
    cin >> x;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    G.resize(N), P.resize(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }
    tour(0);

    touched.assign(N, true);
    base = ask();

    int l = 0, r = edges.size() - 1;
    while (l != r) {
        int m = (l + r + 2) / 2;
        touched.assign(N, false);
        rep(i, m, r + 1) touched[edges[i].first] = true,
                         touched[edges[i].second] = true;
        if (ask() < base) {
            // edge is in untouched vertices
            r = m - 1;
        } else {
            // edge is in touched vertices
            l = m;
        }
    }

    cout << "! " << edges[l].first + 1 << " " << edges[l].second + 1 << endl;
}
