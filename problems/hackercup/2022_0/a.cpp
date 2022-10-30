#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC)
    {
        int N, K;
        cin >> N >> K;
        vector<int> S(128);
        rep(i, N)
        {
            int s;
            cin >> s;
            S[s]++;
        }
        bool ok = true;
        if (N > 2 * K)
            ok = false;
        rep(i, 128) if (S[i] > 2) ok = false;
        cout << "Case #" << tc + 1 << ": " << (ok ? "YES" : "NO") << "\n";
    }
}
