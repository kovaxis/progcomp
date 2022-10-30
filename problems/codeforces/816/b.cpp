#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll N, K, B, S;
vector<ll> ans;

bool solve() {
    ans.assign(N, 0);
    ans[0] = K * B;
    ll diff = S - K * B;
    if (diff < 0) return false;
    rep(i, N) {
        ll mv = min(diff, K - 1);
        diff -= mv;
        ans[i] += mv;
    }
    if (diff > 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K >> B >> S;
        if (solve()) {
            rep(i, N) cout << ans[i] << " \n"[i == N - 1];
        } else {
            cout << "-1\n";
        }
    }
}
