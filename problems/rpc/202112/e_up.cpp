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

template <class K, class V>
using umap = unordered_map<K, V>;

int N;
vector<vector<int>> G;

vector<int> dpmem;

int dp(int);

int rawdp(int board) {
    int p = __builtin_popcount(board) % 2 ? -1 : 1;
    int mscore = INT32_MIN;
    rep(i, N) {
        if (board & (1 << i)) continue;
        int s = p * dp(board | (1 << i));
        for (int j : G[i]) s += board & (1 << j) ? 1 : -1;
        mscore = max(mscore, s);
    }

    if (mscore == INT32_MIN) return 0;
    return mscore * p;
}

int dp(int board) {
    if (dpmem[board] != INT32_MAX) return dpmem[board];
    return dpmem[board] = rawdp(board);
    /*
    cerr << "board " << bitset<20>(board)
         << " results in player1 - player2 score of " << dpmem[board] << endl;
    return dpmem[board];
    // */
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int M;
    cin >> N >> M;
    G.resize(N);
    rep(i, M) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    dpmem.assign(1 << N, INT32_MAX);
    int ans = dp(0);
    if (ans > 0) {
        cout << "player 1" << endl;
    } else if (ans < 0) {
        cout << "player 2" << endl;
    } else {
        cout << "tie" << endl;
    }
}
