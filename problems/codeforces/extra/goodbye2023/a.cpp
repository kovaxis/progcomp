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
        vector<int> B(N);
        rep(i, N) cin >> B[i];

        ll prod = 1;
        rep(i, N) prod *= B[i];

        if (2023 % prod == 0) {
            cout << "YES\n";
            cout << (2023 / prod);
            rep(k, K - 1) cout << " 1";
            cout << "\n";
        } else {
            cout << "NO\n";
        }
    }
}
