#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
// eq[x][y][z] <-> d(x, z) = d(y, z)
bool eq[128][128][128];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        rep(i, N - 1) rep(j, N - i - 1) rep(k, N) {
            char c;
            cin >> c;
            eq[i][i + j][k] = eq[i + j][i][j] = (c == '1');
        }
        rep(i, N) rep(k, N) eq[i][i][k] = true;
    }
}
