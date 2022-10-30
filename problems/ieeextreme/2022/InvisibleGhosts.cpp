#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int W, H;
char M[512][512];

int N;
vector<vector<int>> G;

void add_if_valid(int x, int y, vector<int> &ids) {
    if (x < 0 || x >= W || y < 0 || y >= H) return;
    if (M[x][y] == 'X') return;
    ids.push_back(y * W + x);
}

pair<int, int> id2pos(int id) {
    int x = id % W;
    int y = id / W;
    return {x, y};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> H >> W;
        rep(y, H) rep(x, W) cin >> M[x][y];

        N = W * H;
        G.assign(N, {});
        vector<bool> g_seen(N), p_seen(N);
        vector<int> g_open, g_open2, p_open, p_open2;
        vector<int> g_back(N, -1), p_back(N, -1);
        vector<int> g_since(N, -1), p_since(N, -1);
        rep(x, W) rep(y, H) {
            if (M[x][y] == 'X') continue;
            int id = y * W + x;
            add_if_valid(x, y + 1, G[id]);
            add_if_valid(x - 1, y, G[id]);
            add_if_valid(x + 1, y, G[id]);
            add_if_valid(x, y - 1, G[id]);
            if (M[x][y] == 'G') g_seen[id] = true, g_since[id] = 0, g_open.push_back(id);
            if (M[x][y] == 'P') p_seen[id] = true, p_since[id] = 0, p_open.push_back(id);
        }

        for (int t = 1; g_open.size() != 0 || p_open.size() != 0; t++) {
            for (int u : g_open) {
                for (int v : G[u]) {
                    if (g_seen[v]) continue;
                    g_seen[v] = true;
                    g_open2.push_back(v);
                    g_back[v] = u;
                    g_since[v] = t;
                }
            }
            for (int u : p_open) {
                for (int v : G[u]) {
                    if (p_seen[v]) continue;
                    if (g_seen[v]) continue;
                    p_seen[v] = true;
                    p_open2.push_back(v);
                    p_back[v] = u;
                    p_since[v] = t;
                }
            }
            swap(g_open, g_open2), g_open2.clear();
            swap(p_open, p_open2), p_open2.clear();
        }

        int mx_time = -1, mx_id = -1;
        rep(id, N) {
            if (p_since[id] == -1) continue;
            int t = g_since[id] == -1 ? 1e9 : g_since[id];
            if (t > mx_time) mx_time = t, mx_id = id;
        }

        vector<int> stk;
        int id = mx_id;
        while (id != -1) {
            stk.push_back(id);
            id = p_back[id];
        }

        cout << "Case #" << tc + 1 << ": ";
        if (mx_time == 1e9) cout << "INFINITE";
        else cout << mx_time - 1;
        cout << " ";
        if (stk.size() <= 1) {
            cout << "STAY";
        } else {
            invrep(i, stk.size() - 1) {
                auto [x1, y1] = id2pos(stk[i + 1]);
                auto [x2, y2] = id2pos(stk[i]);
                if (y2 == y1 + 1) cout << "D";
                if (x2 == x1 - 1) cout << "L";
                if (x2 == x1 + 1) cout << "R";
                if (y2 == y1 - 1) cout << "U";
            }
        }
        cout << "\n";
    }
}
