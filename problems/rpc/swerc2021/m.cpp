#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int N, M;
        cin >> N >> M;
        vector<int> r(M), w(M);
        rep(i, M) cin >> r[i] >> w[i];

        int maxr = 0, maxw = 0;
        rep(i, M) maxr = max(maxr, r[i]), maxw = max(maxw, w[i]);
        if (maxr + maxw > N) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        string ans;
        rep(i, maxr) ans += 'R';
        rep(i, maxw) ans += 'W';
        while (ans.size() < N) ans += 'R';
        cout << ans << "\n";
    }
}