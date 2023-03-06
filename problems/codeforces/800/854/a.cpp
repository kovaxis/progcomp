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
        vector<bool> seen(M);
        int taken = 0;
        vector<int> ans(N, -1);
        rep(j, M) {
            int x;
            cin >> x;
            x -= N + 1;
            if (!seen[x]) {
                taken += 1;
                if (N - taken >= 0)
                    ans[N - taken] = j + 1;
            }
            seen[x] = true;
        }
        rep(i, N) cout << ans[i] << " ";
        cout << "\n";
    }
}
