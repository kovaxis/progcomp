#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll M = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        if (N % 2 == 1) {
            cout << "0\n";
            continue;
        }
        ll ans = 1;
        repx(k, 1, N / 2 + 1) ans = ans * k % M;
        ans = ans * ans % M;
        cout << ans << "\n";
    }
}
