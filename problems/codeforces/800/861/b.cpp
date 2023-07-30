#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
vector<vector<ll>> A;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        A.assign(M, vector<ll>(N));
        rep(i, N) rep(j, M) cin >> A[j][i];

        rep(j, M) sort(A[j].begin(), A[j].end());
        ll ans = 0;
        rep(j, M) {
            rep(i, N) {
                ll l = i;
                ll r = N - i - 1;
                ans += A[j][i] * (l - r);
            }
        }
        cout << ans << "\n";
    }
}
