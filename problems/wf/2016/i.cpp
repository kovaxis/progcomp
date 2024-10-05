#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int GN, N, M;
vector<vector<int>> C;
vector<vector<double>> A;

vector<bool> shortest(int U, int V) {
    vector<int> D(GN, (int)1e9);
    vector<int> P(GN, -1);
    priority_queue<pair<int, int>> Q;
    D[U] = 0;
    Q.push({0, U});
    while(Q.size()) {
        auto [d, u] = Q.top();
        d = -d;
        Q.pop();
        if (d < D[u]) continue;

        rep(v, GN) {
            if (D[u] + C[u][v] < D[v]) {
                D[v] = D[u] + C[u][v];
                P[v] = u;
                Q.push({-D[v], v});
            }
        }
    }

    vector<bool> vars(N);
    while(V != U) {
        int u = P[V], v = V;
        vars[u*N+v] = true;
        V = P[V];
    }

    return vars;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> GN;
    C.resize(GN, vector<int>(GN));
    rep(i, GN) rep(j, GN) {
        cin >> C[i][j];
        if (C[i][j] == -1) C[i][j] = 1e9;
    }

    N = GN * GN;

    cin >> M;
    A.resize(M, vector<double>(N+1));
    rep(j, M) {
        int u, v, t;
        cin >> u >> v >> t;
        vector<bool> paths = shortest(u, v);
        rep(i, N) A[j][i] = (double)paths[i];
        A[j][N] = t;
    }

    int Q;
    cin >> Q;
    rep(q, Q) {
        int u, v;
        cin >> u >> v;

    }
}
