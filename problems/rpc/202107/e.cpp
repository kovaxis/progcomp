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

int trans(char c) {
    if (c == ' ') return 36;
    if ('0' <= c and c <= '9') return 26 + c - '0';
    return c - 'A';
}

char not_trans(int x) {
    if (x == 36) return ' ';
    if (26 <= x and x <= 35) return x - 26 + '0';
    return c + 'A';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int mat[n][n];
    rep(i, n) rep(j, n) cin >> mat[i][j];
    string s;
    cin >> s;
    vector<vector<int>> V;
    vector<int> aux;
    string ans = "";
    rep(i, s.length() / n) {
        vector<int> aux;
        rep(j, n) aux.push_back(transform(s[i * s.length() / n + j]));
        rep(j, n) { rep(k, n) ans += not_trans(aux[k]); }
    }
    cout << ans << '\n';
}
