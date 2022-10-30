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

    int T;
    cin >> T;
    rep(tc, T) {
        int N;
        cin >> N;
        vector<int> a(N);
        rep(i, N) cin >> a[i];
        int x = 0, y = N - 1, last = -1, ans = 0;
        while (x <= y) {
            if (a[x] < a[y]) {
                // consume left
                ans += (a[x] >= last);
                last = max(last, a[x]);
                x += 1;
            } else {
                // consume right
                ans += (a[y] >= last);
                last = max(last, a[y]);
                y -= 1;
            }
        }
        cout << "Case #" << tc + 1 << ": " << ans << "\n";
    }
}
