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

ll INF = 1e18;
ll MOD = 1000000007;

int N, Q;
vector<ll> a, b;
vector<ll> wx, wy, qx, qy;
ll ans;

void solve()
{
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    cerr << "a =";
    rep(i, N) cerr << " " << a[i];
    cerr << endl;
    cerr << "b =";
    rep(j, Q) cerr << " " << b[j];
    cerr << endl;

    // solve sum_{i=0..N, j=0..Q} ( b[j] >= a[i] ? (b[j] - a[i])^2 : 0 )
    ll acc = 0, grow = 0, amount = 0, x = min(a[0], b[0]), i = 0;
    rep(j, Q)
    {
        while (x <= b[j])
        {
            // make sure all a's before x are included
            while (i < N && a[i] <= x)
            {
                grow = (grow + 1) % MOD;
                amount += 1;
                i += 1;
            }
            // advance x by 1
            if (x == b[j])
                break;
            acc = (acc + grow) % MOD;
            grow = (grow + 2 * amount % MOD) % MOD;
            x += 1;
        }
        cerr << "dist to b[" << j << "] is " << acc << endl;
        ans = (ans + acc) % MOD;
    }

    rep(i, N) a[i] *= -1;
    rep(j, Q) b[j] *= -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC)
    {
        cin >> N;
        wx.resize(N), wy.resize(N);
        rep(i, N) cin >> wx[i] >> wy[i];
        cin >> Q;
        qx.resize(Q), qy.resize(Q);
        rep(j, Q) cin >> qx[j] >> qy[j];

        ans = 0;
        a = wx, b = qx;
        solve();
        solve();
        a = wy, b = qy;
        solve();
        solve();
        cout << "Case #" << tc + 1 << ": " << ans << "\n";
    }
}
