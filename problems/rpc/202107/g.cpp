#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int n, m;
vector<int> ranking;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    rep(i, n) { ranking.push_back(i); }
    rep(i, m) {
        int win, lose;
        char t;
        cin >> t;
        cin >> win;
        cin >> t;
        cin >> lose;
        win -= 1;
        lose -= 1;
        int winpos, losepos;
        rep(j, n) {
            if (ranking[j] == win) winpos = j;
            if (ranking[j] == lose) losepos = j;
        }
        if (winpos < losepos) continue;
        ranking.erase(ranking.begin() + losepos);
        ranking.insert(ranking.begin() + winpos, lose);
    }
    rep(i, n) cout << "T" << ranking[i] + 1 << " \n"[i == n - 1];
}
