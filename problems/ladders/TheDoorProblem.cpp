// https://codeforces.com/contest/776/problem/D

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int N, M;
vector<int> initial;
vector<vector<int>> rooms;
vector<vector<int>> G;
vector<int> comp;
int C;

bool mark(int u) {
    if (comp[u] != -1) return false;
    comp[u] = C;
    for (int v : G[u]) mark(v);
    return true;
}

int neg(int u) { return (u + M) % (2 * M); }
void connect(int u, int v) {
    cerr << "  connecting " << u + 1 << " with " << v + 1 << endl;
    G[u].push_back(v), G[v].push_back(u);
    u = neg(u), v = neg(v);
    cerr << "  connecting " << u + 1 << " with " << v + 1 << endl;
    G[u].push_back(v), G[v].push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    initial.resize(N), rooms.resize(N);
    rep(i, N) cin >> initial[i];
    rep(j, M) {
        int x;
        cin >> x;
        rep(k, x) {
            int i;
            cin >> i;
            rooms[i - 1].push_back(j);
        }
    }

    G.resize(2 * M);
    rep(i, N) {
        int u = rooms[i][0], v = rooms[i][1];
        // u != v if initial[i] = 0
        // u == v if initial[i] = 1
        cerr << u + 1 << " " << (initial[i] ? "==" : "!=") << " " << v + 1 << endl;
        connect(u, initial[i] ? v : neg(v));
    }

    comp.assign(2 * M, -1), C = 0;
    rep(u, 2 * M) C += mark(u);

    rep(u, 2 * M) cerr << "component[" << u + 1 << "] = " << comp[u] + 1 << endl;

    bool possible = true;
    rep(u, M) if (comp[u] == comp[neg(u)]) possible = false;
    cout << (possible ? "YES\n" : "NO\n");
}
