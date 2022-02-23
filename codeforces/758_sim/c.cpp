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

// strength, player
vector<pair<int, int>> str[2];

// for each map, pos -> player
// the player at position i can win against all players in positions j <= i in
// the corresponding map
vector<int> pos2player[2];
vector<int> player2pos[2];
// for each map `m`, pos in map `m` -> pos in map `!m`
vector<int> pos2otherpos[2];

string ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        rep(m, 2) str[m].resize(N), pos2player[m].resize(N),
            player2pos[m].resize(N), pos2otherpos[m].resize(N);
        rep(m, 2) rep(i, N) {
            int s;
            cin >> s;
            str[m][i] = {s, i};
        }
        rep(m, 2) sort(str[m].begin(), str[m].end());
        rep(m, 2) rep(i, N) pos2player[m][i] = str[m][i].second;
        rep(m, 2) rep(i, N) player2pos[m][pos2player[m][i]] = i;
        rep(m, 2) rep(i, N) pos2otherpos[m][i] =
            player2pos[!m][pos2player[m][i]];

                rep(m, 2) rep(i, 1, N) pos2otherpos[m][i] =
            max(pos2otherpos[m][i], pos2otherpos[m][i - 1]);

        invrep(i, N) rep(m, 2) {
            int b = pos2otherpos[m][i];
            int a = pos2otherpos[!m][b];
            if (a > i) {
                int newb = pos2otherpos[m][a];
                int newa = pos2otherpos[!m][newb];
                pos2otherpos[!m][b] = newa;
                pos2otherpos[m][i] = newb;
            }
        }

        ans.resize(N);
        rep(i, N) {
            bool canwin = pos2otherpos[0][player2pos[0][i]] >= N - 1 ||
                          pos2otherpos[1][player2pos[1][i]] >= N - 1;
            ans[i] = canwin ? '1' : '0';
        }
        cout << ans << "\n";
    }
}
