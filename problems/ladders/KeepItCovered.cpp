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

int N;
int W, H;
int nodes[32][32][2];
vector<vector<int>> adj;

vector<bool> seen;
vector<int> mt;

bool subkuhn(int i) {
    if (seen[i]) return false;
    seen[i] = true;
    for (int to : adj[i])
        if (mt[to] == -1 || subkuhn(mt[to])) {
            mt[to] = i;
            return true;
        }
    return false;
}

int kuhn() {
    int total = 0;
    rep(i, N) mt[i] = -1;
    rep(i, N) {
        rep(j, N) seen[j] = false;
        total += subkuhn(i);
    }
    return total;
}

void add_nodes(int x, int y, vector<int>& into) {
    if (x < 0 || x >= W || y < 0 || y >= H) return;
    rep(i, 2) {
        if (nodes[x][y][i] == -1) return;
        into.push_back(nodes[x][y][i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        if (!(cin >> H)) break;
        if (!(cin >> W)) break;
        N = 0;
        rep(y, H) rep(x, W) {
            char c;
            cin >> c;
            if (c == 'o') {
                nodes[x][y][0] = N++;
                nodes[x][y][1] = -1;
            } else {
                nodes[x][y][0] = N++;
                nodes[x][y][1] = N++;
            }
        }

        seen.resize(N);
        mt.resize(N);
        adj.clear();
        adj.resize(N);
        rep(x, W) rep(y, H) rep(i, 2) {
            if (nodes[x][y][i] == -1) break;
            auto& a = adj[nodes[x][y][i]];
            add_nodes(x - 1, y, a);
            add_nodes(x + 1, y, a);
            add_nodes(x, y - 1, a);
            add_nodes(x, y + 1, a);
        }

        cout << (kuhn() == N ? "Y\n" : "N\n");
    }
}
