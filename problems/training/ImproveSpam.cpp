#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll MOD = 1000000007;

int n, m;
vector<int> lists[2001];

// addr
// clients
ll dp[2001];

// addr
// dup, dedup
pair<ll, ll> sendto(int addr) {
    ll& result = dp[addr];
    if (result != -1) {
        return {result, 0};
    }
    if (addr >= m) {
        result = 1;
        return {1, 1};
    }
    ll dup = 0, dedup = 0;
    for (int subaddr : lists[addr]) {
        auto sub = sendto(subaddr);
        dup = (dup + sub.first) % MOD;
        dedup = (dedup + sub.second) % MOD;
    }
    result = dup;
    return {dup, dedup};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    rep(i, m) {
        int l;
        cin >> l;
        rep(j, l) {
            int addr;
            cin >> addr;
            addr -= 1;
            lists[i].push_back(addr);
        }
    }
    rep(i, n) { dp[i] = -1; }

    auto out = sendto(0);
    cout << out.first << " " << out.second << endl;
}
