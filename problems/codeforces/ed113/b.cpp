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
int mat[64][64];
int req[64];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    string s;
    cin >> T;
    rep(t, T) {
        cin >> N >> s;
        rep(i, N) rep(j, N) mat[i][j] = 0;
        int k = 0;
        rep(i, N) {
            if (s[i] == '1') continue;
            req[k++] = i;
        }
        if (k == 1 || k == 2) {
            cout << "NO\n";
            continue;
        }
        rep(l, k) {
            int i = req[l];
            int j = req[(l + 1) % k];
            mat[i][j] = 1;
            mat[j][i] = -1;
        }
        cout << "YES\n";
        rep(i, N) {
            rep(j, N) if (i == j) cout << "X";
            else if (mat[i][j] == 0) cout << "=";
            else if (mat[i][j] > 0) cout << "+";
            else if (mat[i][j] < 0) cout << "-";
            cout << "\n";
        }
    }
}
