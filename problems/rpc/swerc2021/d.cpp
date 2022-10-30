#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)
int DPI[202][202][2];
int DP[202][202];
string adn[2];
bool insertable(int l, int r, int s) {
    if (l > r) return true;
    if (DPI[l][r][s] != -1) return DPI[l][r][s];
    for (int i = l; i < r; i++) {
        if (insertable(l, i, s) && insertable(i + 1, r, s))
            return DPI[l][r][s] = true;
    }
    if (r - l + 1 >= 2) {
        if (adn[s][l] == 'A' && adn[s][r] == 'A' && insertable(l + 1, r - 1, s))
            return DPI[l][r][s] = true;
        if (adn[s][l] == 'B' && adn[s][r] == 'B' && insertable(l + 1, r - 1, s))
            return DPI[l][r][s] = true;
        if (adn[s][l] == 'C' && adn[s][r] == 'C' && insertable(l + 1, r - 1, s))
            return DPI[l][r][s] = true;
    }
    if (r - l + 1 >= 4) {
        if (adn[s][l] == 'A' && adn[s][r - 2] == 'B' && adn[s][r - 1] == 'A' &&
            adn[s][r] == 'B' && insertable(l + 1, r - 3, s))
            return DPI[l][r][s] = true;
        if (adn[s][l] == 'A' && adn[s][l + 1] == 'B' && adn[s][r - 1] == 'A' &&
            adn[s][r] == 'B' && insertable(l + 2, r - 2, s))
            return DPI[l][r][s] = true;
        if (adn[s][l] == 'A' && adn[s][l + 1] == 'B' && adn[s][l + 2] == 'A' &&
            adn[s][r] == 'B' && insertable(l + 3, r - 1, s))
            return DPI[l][r][s] = true;
        if (adn[s][l] == 'B' && adn[s][r - 2] == 'C' && adn[s][r - 1] == 'B' &&
            adn[s][r] == 'C' && insertable(l + 1, r - 3, s))
            return DPI[l][r][s] = true;
        if (adn[s][l] == 'B' && adn[s][l + 1] == 'C' && adn[s][r - 1] == 'B' &&
            adn[s][r] == 'C' && insertable(l + 2, r - 2, s))
            return DPI[l][r][s] = true;
        if (adn[s][l] == 'B' && adn[s][l + 1] == 'C' && adn[s][l + 2] == 'B' &&
            adn[s][r] == 'C' && insertable(l + 3, r - 1, s))
            return DPI[l][r][s] = true;
    }
    return DPI[l][r][s] = false;
}

bool possible(int a, int b) {
    if (a >= adn[0].length() && b >= adn[1].length()) return true;
    if (DP[a][b] != -1) return DP[a][b];
    if (a < adn[0].length() && b < adn[1].length())
        if (adn[0][a] == adn[1][b]) {
            if (possible(a + 1, b + 1)) return DP[a][b] = true;
        }
    repx(i, a + 1, adn[0].length() + 1) if (insertable(a, i - 1, 0) &&
                                            possible(i, b)) return DP[a][b] =
        true;
    repx(i, b + 1, adn[1].length() + 1) if (insertable(b, i - 1, 1) &&
                                            possible(a, i)) return DP[a][b] =
        true;

    return DP[a][b] = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        rep(a, 202) rep(b, 202) {
            DPI[a][b][0] = -1;
            DPI[a][b][1] = -1;
            DP[a][b] = -1;
        }
        cin >> adn[0] >> adn[1];

        if (possible(0, 0))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}