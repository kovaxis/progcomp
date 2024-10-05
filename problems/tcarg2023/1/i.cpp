#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

ll N, M;
vector<ll> C;

ll solve(ll P) {
    // solve the maximum spend with P rounds

    // find the free positions after A
    vector <
}

int main() {
    cin >> N >> M;
    C.resize(N);
    rep(i, N) cin >> C[i];

    ll ans = 0;
    rep(P, (M + N - 1) / N) {
        ans = max(ans, solve(P));
    }
    cout << ans << endl;
}