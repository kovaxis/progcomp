// https://www.codechef.com/COOK126A/problems/MEXSUB/

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

const ll MOD = 1e9 + 7;

int a[100001];
int domex[100001];

int num_idx[100001];
int dp[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T, N, mex;
    set<int> min_idx;
    cin >> T;
    rep(t, T) {
        cin >> N;
        rep(i, N) cin >> a[i];

        {
            rep(i, N) domex[i] = a[i];
            sort(domex, domex + N);
            mex = 0;
            rep(i, N + 1) if (domex[i] == mex) mex++;
            else if (domex[i] > mex) break;
            cerr << "mex = " << mex << endl;
        }

        min_idx.clear();
        rep(i, N) num_idx[a[i]] = -1;
        dp[0] = 1;
        rep(i, N) {
            if (a[i] < mex) {
                if (num_idx[a[i]] != -1) min_idx.erase(num_idx[a[i]]);
                min_idx.insert(i);
                num_idx[a[i]] = i;
            }
            if (min_idx.size() < mex) {
                dp[i + 1] = dp[i];
            } else {
                int l = min_idx.empty() ? i : *min_idx.begin();
                dp[i + 1] = (dp[i] + dp[l]) % MOD;
            }
        }
        cout << (dp[N] - dp[N - 1] + MOD) % MOD << '\n';
    }
}
