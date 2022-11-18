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

void dijkstra(const vector<vector<pair<ll, int>>> &G, vector<pair<ll, int>> &D, int src) {
    priority_queue<pair<ll, int>> q;
    D.assign(G.size(), {1e18, -1});
    D[src] = {0, -1}, q.push({0, src});
    while (!q.empty()) {
        auto [d, u] = q.top();
        d = -d, q.pop();
        if (d > D[u].first) continue;
        for (auto [w, v] : G[u])
            if (d + w < D[v].first) {
                D[v] = {d + w, u};
                q.push({-d - w, v});
            }
    }
}

int N, M;
vector<string> mp;

int sig(int i, int j) {
    return (i + j) & 1;
}

template <class OP>
void inside(vector<vector<bool>> &canput, int i, int j, OP op) {
    if (i >= 0 && i < N && j >= 0 && j < M && canput[i][j]) op(i, j);
}

pair<ll, vector<string>> solve(int x) {
    cerr << "solving for parity = " << x << endl;
    vector<vector<pair<ll, int>>> G(N * M + 2);
    vector<vector<bool>> canput(N, vector<bool>(M, true));

    rep(i, N) rep(j, M) if (sig(i, j) != x) {
        canput[i][j] = false;
        if (mp[i][j] == '#') {
            inside(canput, i - 1, j, [&](int i, int j) { canput[i][j] = false; });
            inside(canput, i + 1, j, [&](int i, int j) { canput[i][j] = false; });
            inside(canput, i, j - 1, [&](int i, int j) { canput[i][j] = false; });
            inside(canput, i, j + 1, [&](int i, int j) { canput[i][j] = false; });
        }
    }

    cerr << "got canput" << endl;

    rep(i, N) rep(j, M) if (canput[i][j]) {
        inside(canput, i - 1, j - 1, [&](int ii, int jj) { G[i * M + j].push_back({mp[ii][jj] == '.', ii * M + jj}); });
        inside(canput, i + 1, j - 1, [&](int ii, int jj) { G[i * M + j].push_back({mp[ii][jj] == '.', ii * M + jj}); });
        inside(canput, i - 1, j + 1, [&](int ii, int jj) { G[i * M + j].push_back({mp[ii][jj] == '.', ii * M + jj}); });
        inside(canput, i + 1, j + 1, [&](int ii, int jj) { G[i * M + j].push_back({mp[ii][jj] == '.', ii * M + jj}); });
    }

    cerr << "built links" << endl;

    rep(i, N) {
        inside(canput, i, 0, [&](int i, int j) {
            G[N * M].push_back({mp[i][j] == '.', i * M + j});
            G[i * M + j].push_back({0, N * M});
        });
        inside(canput, i, M - 1, [&](int i, int j) {
            G[N * M + 1].push_back({mp[i][j] == '.', i * M + j});
            G[i * M + j].push_back({0, N * M + 1});
        });
    }

    cerr << "built source/sink" << endl;

    vector<pair<ll, int>> D(N * M + 2);
    dijkstra(G, D, N * M);

    cerr << "solved" << endl;

    if (D[N * M + 1].second == -1) return {1e18, {}};

    // rebuild solution
    vector<string> mp2 = mp;
    int u = D[N * M + 1].second;
    while (u != N * M) {
        int i = u / M, j = u % M;
        mp2[i][j] = '#';
        u = D[u].second;
    }

    cerr << "rebuilt solution" << endl;

    return {D[N * M + 1].first, mp2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cerr << "solving testcase " << TC << endl;
        cin >> N >> M;
        mp.resize(N);
        rep(i, N) cin >> mp[i];

        auto s0 = solve(0), s1 = solve(1);
        if (s1.first < s0.first) swap(s0, s1);

        cerr << "printing result" << endl;

        if (s0.first == 1e18) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            rep(i, N) cout << s0.second[i] << "\n";
        }
    }
}
