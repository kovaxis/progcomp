#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int W, H;
vector<vector<char>> M, M2;

bool can_place(int x, int y)
{
    if (x < 0 || x >= W)
        return false;
    if (y < 0 || y >= H)
        return false;
    if (M[x][y] == '#' || M2[x][y])
        return false;
    return true;
}

void maybe_mark(int x, int y)
{
    if (x < 0 || x >= W)
        return;
    if (y < 0 || y >= H)
        return;
    if (M[x][y] == '#' || M2[x][y])
        return;
    int cnt = 0;
    cnt += can_place(x + 1, y);
    cnt += can_place(x - 1, y);
    cnt += can_place(x, y + 1);
    cnt += can_place(x, y - 1);
    if (cnt >= 2)
        return;
    M2[x][y] = 1;
    maybe_mark(x + 1, y);
    maybe_mark(x - 1, y);
    maybe_mark(x, y + 1);
    maybe_mark(x, y - 1);
}

bool solve()
{
    rep(x, W) rep(y, H) maybe_mark(x, y);
    rep(x, W) rep(y, H) if (M2[x][y] && M[x][y] == '^') return false;
    rep(x, W) rep(y, H) if (!M2[x][y] && M[x][y] == '.') M[x][y] = '^';
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
        M2.assign(W, vector<char>(H));
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
