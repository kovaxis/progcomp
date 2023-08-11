#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

const ll MOD = 998244353;

ll mul(ll x, ll y) { return x * y % MOD; }
ll add(ll x, ll y) { return (x + y) % MOD; }

ll binexp(ll a, ll e, ll M) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a % M;
        a = a * a % M;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M = MOD) { return binexp(a, M - 2, M); }

const int MATCH = 0;
const int NORMAL = 1;
const int CLEAR = 2;

int N;
vector<vector<int>> G;

vector<ll> dp[3];

void getdp(int u, int p) {
    if (dp[0][u] != -1) return;

    ll any = 1;
    for (int v : G[u])
        if (v != p) {
            getdp(v, u);
            any = mul(any, add(dp[NORMAL][v], dp[CLEAR][v]));
        }
    dp[MATCH][u] = any;
    cerr << "MATCH[" << u + 1 << "] = " << any << endl;

    ll normal = 0;
    for (int v : G[u])
        if (v != p) {
            ll partial = mul(any, multinv(add(dp[NORMAL][v], dp[CLEAR][v])));
            partial = mul(partial, dp[MATCH][v]);
            normal = add(normal, partial);
        }
    dp[NORMAL][u] = normal;
    cerr << "NORMAL[" << u + 1 << "] = " << normal << endl;

    ll clear = 1;
    for (int v : G[u])
        if (v != p) {
            clear = mul(clear, dp[CLEAR][v]);
        }
    clear = add(clear, normal);
    dp[CLEAR][u] = clear;
    cerr << "CLEAR[" << u + 1 << "] = " << clear << endl;
}

int main() {
    cin >> N;
    G.resize(N);
    rep(j, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    rep(k, 3) dp[k].resize(N, -1);
    getdp(0, 0);
    cout << dp[CLEAR][0] << endl;
}
