#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int W, H;
vector<vector<char>> M;

bool solve()
{
    int trees = 0;
    rep(x, W) rep(y, H) trees += (M[x][y] == '^');
    if (trees == 0)
        return true;
    if (W == 1 || H == 1)
        return false;
    rep(x, W) rep(y, H) M[x][y] = '^';
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC)
    {
        cin >> H >> W;
        M.assign(W, vector<char>(H));
        rep(y, H) rep(x, W) cin >> M[x][y];
        cout << "Case #" << tc + 1 << ": ";
        if (solve())
        {
            cout << "Possible\n";
            rep(y, H)
            {
                rep(x, W) cout << M[x][y];
                cout << "\n";
            }
        }
        else
        {
            cout << "Impossible\n";
        }
    }
}
