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
        int N;
        cin >> N;
        vector<int> A(2 * N);
        rep(i, 2 * N) cin >> A[i];
        sort(A.begin(), A.end());
        ll ans = 0;
        rep(i, N) ans += min(A[2 * i], A[2 * i + 1]);
        cout << ans << "\n";
    }
}
