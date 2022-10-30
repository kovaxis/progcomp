#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int INF = 1e9;

string a, b;

int equpto;

int dpmem[128][128];
int dp(int i, int j) {
    if (dpmem[i][j] != -1) return dpmem[i][j];
    int ans = INF;
    if (i > 0 && j > 0 && a[i - 1] == b[j - 1])
        ans = min(ans, dp(i - 1, j - 1) + 2);
    if (i > 0) ans = min(ans, dp(i - 1, j) + 1);
    if (j > 0) ans = min(ans, dp(i, j - 1) + 1);
    if (i == j && i <= equpto) ans = 0;
    return dpmem[i][j] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> b;

    equpto = min(a.size(), b.size());
    rep(i, equpto) {
        if (a[i] != b[i]) {
            equpto = i;
            break;
        }
    }

    rep(i, a.size() + 1) rep(j, b.size() + 1) dpmem[i][j] = -1;

    cout << dp(a.size(), b.size()) << endl;
}
