#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

int N;
int P[1024][1024];
priority_queue<pair<int, pair<int, int>>> Q;
vector<pair<int, int>> ans;
int score;

void setp(int i, int j, int p) {
    if (p <= P[i][j]) return;
    if (i == j) return;
    P[i][j] = p;
    if (i >= j) return;
    Q.push({p, {i, j}});
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    rep(i, N) rep(j, N) cin >> P[i][j];

    rep(i, N) rep(j, N) if (i < j) Q.push({P[i][j], {i, j}});

    while (!Q.empty()) {
        auto [i, j] = Q.top().second;
        int p = Q.top().first;
        Q.pop();
        if (p != P[i][j]) continue;
        if (p == 0) continue;

        // i plays against j, i wins (i < j)
        score += p;
        ans.push_back({i, j});

        // i inherits j
        rep(k, N) setp(i, k, max(P[i][k], P[j][k]));
        rep(k, N) setp(k, i, max(P[k][i], P[k][j]));

        // kill j
        rep(k, N) P[j][k] = 0, P[k][j] = 0;

        cerr << "played " << i + 1 << " against " << j + 1 << endl;
        cerr << "new P:" << endl;
        rep(i, N) {
            rep(j, N) cerr << P[i][j] << " ";
            cerr << endl;
        }
    }

    cout << score << "\n";
    for (auto [i, j] : ans) {
        cout << i + 1 << " " << j + 1 << "\n";
    }
}
