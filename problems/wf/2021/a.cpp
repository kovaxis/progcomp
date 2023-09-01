#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int W, H, K;
vector<int> A;
vector<vector<int>> G[2];

struct P {
    int x, y;

    P operator+(P r) { return {x + r.x, y + r.y}; }
    P operator-(P r) { return {x - r.x, y - r.y}; }

    int id() {
        if (x < 0 || x >= W || y < 0 || y >= H) return -1;
        return y * W + x;
    }

    friend istream &operator>>(istream &s, P &p) {
        return s >> p.x >> p.y;
    }
};

void dfs(int u) {
    int k = A[u];
    for (int v : G[k][u]) {
        if (A[v] == -1) {
            A[v] = k;
            dfs(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> W >> H >> K;
    A.resize(W * H, -1);
    G[0].resize(W * H), G[1].resize(W * H);
    rep(i, K) {
        P w;
        cin >> w;
        int b;
        cin >> b;
        vector<bool> at(W * H, false);
        rep(j, b) {
            P p;
            cin >> p;
            p = p - P{1, 1};
            at[p.id()] = true;
        }
        rep(y, H) rep(x, W) {
            int dst = (P{x, y}).id();
            int src = (P{x, y} - w).id();
            if (at[dst]) {
                A[dst] = 1;
                if (src != -1) A[src] = 0;
            } else {
                if (src == -1) {
                    A[dst] = 0;
                } else {
                    G[1][dst].push_back(src);
                    G[0][src].push_back(dst);
                }
            }
        }
    }

    rep(u, W * H) if (A[u] != -1) dfs(u);

    rep(m, 2) {
        rep(y, H) {
            rep(x, W) {
                int k = A[(P{x, y}).id()];
                if (k == 1 || (k == -1 && m)) {
                    cout << "#";
                } else {
                    cout << ".";
                }
            }
            cout << "\n";
        }

        if (m == 0) cout << "\n";
    }
}
