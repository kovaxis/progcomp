#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N, M;
        cin >> N >> M;
        int ans = 0;
        ans += 2 * (N - 1 + M - 1);
        int tp = max(max(N, M) - 2, 0);
        ans -= tp;
        cout << ans << "\n";
    }
}
