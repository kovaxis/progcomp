#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

int N = 100;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> N;
    getline(cin, s);
    vector<vector<bool>> mp(N, vector<bool>(N)), mp2(N, vector<bool>(N));
    mp[N / 2][N / 2] = 1;
    while (true) {
        rep(i, N) {
            rep(j, N) {
                cout << " " << ".#"[mp[i][j]];
            }
            cout << endl;
        }
        cout << endl;

        getline(cin, s);

        rep(i, N) rep(j, N) {
            bool x = 0;
            repx(ii, max(i - 1, 0), min(i + 2, N)) repx(jj, max(j - 1, 0), min(j + 2, N)) x ^= mp[ii][jj];
            mp2[i][j] = x;
        }
        swap(mp, mp2);
    }
}
