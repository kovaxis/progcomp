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

const ll MOD = 998244353;

int N, M;
vector<int> a;
vector<ll> mex[2];

void add(ll& x, ll y) { x = (x + y + MOD) % MOD; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.resize(N), mex[0].assign(N + 2, 0), mex[1].assign(N + 2, 0);
        rep(i, N) cin >> a[i];

        mex[0][0] = 1;
        rep(i, N) {
            int x = a[i];
            // cerr << "processing element " << x << endl;

            rep(k, 2) add(mex[k][x + 1], mex[k][x + 1]);
            if (x - 1 >= 0) add(mex[1][x - 1], mex[1][x - 1]);
            if (x - 1 >= 0) add(mex[1][x - 1], mex[0][x - 1]);
            add(mex[0][x + 1], mex[0][x]);

            /*cerr << "mex[N] sequences:";
            rep(j, M + 1) cerr << " " << mex[0].query(j, j);
            cerr << endl;
            cerr << "mex[Y] sequences:";
            rep(j, M + 1) cerr << " " << mex[1].query(j, j);
            cerr << endl;*/
        }
        ll ans = MOD - 1;
        rep(k, 2) for (ll x : mex[k]) add(ans, x);
        cout << ans << "\n";
    }
}
