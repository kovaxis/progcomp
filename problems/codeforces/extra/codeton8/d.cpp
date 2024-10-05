#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Set {
    vector<ll> a;
    ll offset = 0;

    ll to_out(ll in) { return in + offset; }
    ll to_in(ll out) { return out - offset; }
};

int N, K;
ll A[1024][1024];
vector<Set> dp;
vector<ll> ans;

void solve() {
    N += 1;

    dp.assign(N + 1, {});
    dp[0].a.push_back(dp[0].to_in(0));
    rep(idx, N) {
        invrep(i, N) swap(dp[i], dp[i + 1]);

        vector<int> nxt(N + 1);
        priority_queue<pair<ll, int>> que;
        repx(n, 1, N + 1) if (dp[n].a.size()) {
            que.push({dp[n].to_out(dp[n].a[0]), n});
        }
        while (que.size() && (int)dp[0].a.size() < K) {
            auto [_, n] = que.top();
            que.pop();

            ll v = dp[n].to_out(dp[n].a[nxt[n]]);
            nxt[n] += 1;

            dp[0].a.push_back(dp[0].to_in(v));

            if (nxt[n] < (int)dp[n].a.size()) {
                que.push({dp[n].to_out(dp[n].a[nxt[n]]), n});
            }
        }

        repx(n, 1, N + 1) {
            if (idx - n + 1 >= 0) {
                dp[n].offset -= A[idx - n + 1][idx];
                dp[n].offset += A[idx - n + 1][idx + 1];
            }
        }
    }

    ans.resize(K);
    assert((int)dp[0].a.size() >= K);
    rep(i, K) ans[i] = dp[0].to_out(dp[0].a[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        memset(&A, 0, sizeof(A));
        rep(i, N) repx(j, i, N) cin >> A[i][j + 1];
        solve();
        rep(k, K) cout << ans[k] << " ";
        cout << "\n";
    }
}
