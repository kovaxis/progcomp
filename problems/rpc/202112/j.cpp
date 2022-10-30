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

int N, P, T;
vector<vector<pair<int, ll>>> G;

vector<vector<vector<ll>>> reachwithout;

vector<vector<ll>> dpmem;
// get the distance required to drive from
ll dp(int p, int t) {}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int M;
    cin >> N >> M >> P >> T;
    rep(i, M) {
        int a, b, l;
        cin >> a >> b >> l;
        G[a - 1].push_back({b - 1, l});
        G[b - 1].push_back({a - 1, l});
    }

    reachwithout.assign(N, vector<vector<ll>>(N, vector<ll>(N, )));
}
