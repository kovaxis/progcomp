#pragma GCC optimize("Ofast")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
ll INF = 1e15;
ll N, K;
vector<vector<ll>> A;
vector<vector<ll>> dp;

#define cerr \
    if (0) cerr

ll DP(int n, int r) {
    if (dp[n][r] != -1) {
        return dp[n][r];
    }

    dp[n][r] = INF;

    rep(L, 2) rep(R, 2) {
        ll cnt[2];
        rep(k, 2) cnt[k] = A[n][k];
        rep(k, 2) cnt[k] -= (L == k) + (R == k);
        if (cnt[0] < 0 || cnt[1] < 0) {
            // impossible
            continue;
        }
        if (DP(n - 1, L) + 1 > K) {
            // impossible
            continue;
        }

        if (DP(n - 1, 0) > K || DP(n - 1, 1) > K) {
            continue;
        }

        // amount of groups of opposite sign to L
        ll diff_groups = min(cnt[!L], cnt[L] + (L == R));
        // amount of groups of same sign as L
        ll same_groups = max(diff_groups - (L == R), 0ll);
        // alternate
        cnt[!L] -= diff_groups;
        cnt[L] -= same_groups;
        // place at start
        ll start = min(K - DP(n - 1, L) - 1, cnt[L]);
        cnt[L] -= start;
        // place differents into middle groups
        ll midspace_diff = diff_groups * (K - 1);
        midspace_diff = min(midspace_diff, cnt[!L]);
        cnt[!L] -= midspace_diff;
        // place sames into middle groups
        ll midspace_same = same_groups * (K - 1);
        midspace_same = min(midspace_same, cnt[L]);
        cnt[L] -= midspace_same;
        // the remainder must go in R
        if (cnt[!R] > 0) {
            // not enough space for !R
            continue;
        }
        if (cnt[R] + 1 > K) {
            continue;
        }
        cerr << "placed 1 + " << start << " of " << L << " at start, 1 of " << R << " at end, " << diff_groups << " groups of " << !L << ", " << same_groups << " of " << L << ", " << midspace_diff << " at middle groups of different, " << midspace_same << " at middle groups of same, leaving " << cnt[R] << " to insert at end" << endl;
        if (R == r) {
            cerr << "dp[" << n << "][" << r << "] with L " << L << " and R " << R << ": " << 1 + cnt[R] << endl;
            dp[n][r] = min(dp[n][r], 1 + cnt[R]);
        } else {
            cerr << "dp[" << n << "][" << r << "] with L " << L << " and R " << R << ": " << 0 << endl;
            dp[n][r] = 0;
        }
    }

    cerr << "dp[" << n << "][" << r << "] = " << dp[n][r] << endl;

    /*

    if(A[n][r] == 0){
        return dp[n][r];
    }
    if(A[n][1 - r] == 0){
        if(DP(n-1, 1 - r) <= K){
            dp[n][r] = A[n][r];
        }
        else{
            dp[n][r] = DP(n-1, r) + A[n][r];
        }
        return dp[n][r];
    }

    if(DP(n-1, 0) <= K){

    }*/

    return dp[n][r];
}

int main() {

    cin >> N >> K;

    A.resize(N + 1, vector<ll>(2, 0));
    dp.resize(N + 1, vector<ll>(2, -1));
    for (int i = 1; i <= N; i++) {
        cin >> A[i][0];
    }
    for (int i = 1; i <= N; i++) {
        cin >> A[i][1];
    }

    dp[0][0] = 0;
    dp[0][1] = 0;

    if (min(DP(N, 0), DP(N, 1)) <= K) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}