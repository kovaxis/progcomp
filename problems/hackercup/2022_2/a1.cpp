#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0)   \
    cerr

int N;
string s;
vector<vector<int>> acc;

int getcnt(char k, int l, int r)
{
    return acc[k][r] - acc[k][l];
}

bool almost_eq(int l, int m, int r, int invert)
{
    int differ = 0;
    repx(k, 'a', 'z' + 1)
    {
        int diff = getcnt(k, m, r) - getcnt(k, l, m);
        diff *= invert;
        if (diff == 0)
            continue;
        if (diff != 1)
            return false;
        differ += diff;
    }
    if (differ > 1)
        return false;
    return true;
}

bool is_valid(int l, int r)
{
    if ((r - l) % 2 == 0)
        return false;
    return almost_eq(l, (l + r) / 2, r, 1) || almost_eq(l, (l + r + 1) / 2, r, -1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC)
    {
        cerr << "reading string" << endl;
        cin >> s;
        N = s.size();

        acc.assign(128, vector<int>(N + 1));
        rep(i, N) acc[s[i]][i + 1] = 1;
        cerr << "built acc" << endl;
        for (auto &a : acc)
            rep(i, N) a[i + 1] += a[i];

        int Q, ans = 0;
        cin >> Q;
        rep(q, Q)
        {
            int l, r;
            cin >> l >> r;
            l -= 1;
            ans += is_valid(l, r);
        }

        cout << "Case #" << tc + 1 << ": " << ans
             << "\n";
    }
}
