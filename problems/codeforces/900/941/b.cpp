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
        int N, K;
        cin >> N >> K;

        int b = 1 << (31 - __builtin_clz(K));
        vector<int> ans;
        for (int i = 1; i <= N; i *= 2) {
            if (i != b) ans.push_back(i);
        }
        ans.push_back(K + 1);
        ans.push_back(K - b);
        ans.push_back(2 * b + K);

        cout << ans.size() << "\n";
        for (int x : ans) cout << x << " ";
        cout << "\n";
    }
}
