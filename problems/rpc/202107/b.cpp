#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)
#define ff first
#define ss second

int n, m, k;
string s;
int dr[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dc[] = {-1, 0, 1, 1, 1, 0, -1, -1};
vector<ii> S;
char mat[100][100];

bool backtrack(int c, int x, int i, int j) {
    if (c > k) return false;
    if (c == k and x == s.length()) return true;
    rep(h, 8) {
        int di = i + dr[h], dj = j + dc[h];
        if (0 <= di and di < n and 0 <= dj and dj < m and mat[di][dj] == s[x]) {
            int aux = (S.size() == 0                                     ? 0
                       : (S.back().ff == dr[h] and S.back().ss == dc[h]) ? 0
                                                                         : 1);
            S.emplace_back(dr[h], dc[h]);
            if (backtrack(c + aux, x + 1, di, dj)) {
                return true;
            }
            S.pop_back();
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    set<pair<char, char>> pares;
    rep(i, n) rep(j, m) cin >> mat[i][j];
    rep(i, n) rep(j, m) {
        rep(h, 8) {
            int di = i + dr[h], dj = j + dc[h];
            if (0 <= di and di < n and 0 <= dj and dj < m) {
                pares.insert({mat[i][j], mat[di][dj]});
                pares.insert({mat[di][dj], mat[i][j]});
            }
        }
    }
    cin >> k >> s;
    bool yes = false;
    rep(i, s.length() - 1) {
        if (!pares.count({s[i], s[i + 1]})) {
            cout << "No\n";
            cerr << "Espc\n";
            return 0;
        }
    }
    rep(i, n)
        rep(j, m) if (!yes and mat[i][j] == s[0]) if (backtrack(0, 1, i, j)) {
        yes = true;
        break;
    }
    if (yes)
        cout << "Yes\n";
    else
        cout << "No\n";
}
}
