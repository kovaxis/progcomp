#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
vector<pair<int, int>> ordered;
int nxt_order;
vector<vector<int>> board;
vector<vector<bool>> marked;
vector<vector<char>> ans;
vector<pair<int, int>> que;

pair<int, int> largest_unmarked() {
    while (nxt_order >= 0) {
        auto pos = ordered[nxt_order];
        if (!marked[pos.first][pos.second]) return pos;
        nxt_order -= 1;
    }
    return {-1, -1};
}

void mark(pair<int, int> pos, char m) {
    ans[pos.first][pos.second] = m;
    marked[pos.first][pos.second] = true;
}

int dist(pair<int, int> p1, pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void visit(pair<int, int> p) {
    if (p.first < 0 || p.first >= N || p.second < 0 || p.second >= N) return;
    if (marked[p.first][p.second]) return;
    que.push_back(p);
}

void mark_bfs(pair<int, int> center) {
    que.clear();

    repx(di, -K - 1, K + 2) {
        int dj = K + 1 - abs(di);
        rep(k, 2) {
            pair<int, int> p = {center.first + di, center.second + dj};
            visit(p);
            if (dj == -dj) break;
            dj = -dj;
        }
    }

    int i = 0;
    while (i < que.size()) {
        auto p = que[i];
        i += 1;
        if (marked[p.first][p.second]) continue;
        mark(p, 'G');
        if (p.first <= center.first) visit({p.first - 1, p.second});
        if (p.first >= center.first) visit({p.first + 1, p.second});
        if (p.second <= center.second) visit({p.first, p.second - 1});
        if (p.second >= center.second) visit({p.first, p.second + 1});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    board.resize(N, vector<int>(N));
    rep(i, N) rep(j, N) cin >> board[i][j];
    rep(i, N) rep(j, N) board[i][j] -= 1;

    ordered.resize(N * N);
    rep(i, N) rep(j, N) ordered[board[i][j]] = {i, j};
    nxt_order = N * N - 1;

    // rep(i, N * N) cerr << "ordered[" << i << "] = " << ordered[i].first << ",
    // "
    //                   << ordered[i].second << endl;

    marked.resize(N, vector<bool>(N));
    ans.resize(N, vector<char>(N));

    while (true) {
        auto maxp = largest_unmarked();
        // cerr << "cur max is " << maxp.first << ", " << maxp.second << endl;
        if (maxp.first == -1) break;
        mark(maxp, 'M');
        mark_bfs(maxp);
    }

    rep(i, N) {
        rep(j, N) cout << ans[i][j];
        cout << "\n";
    }
}
