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
        ll N, K;
        cin >> N >> K;
        if (K == 4 * N - 2) cout << 2 * N << "\n";
        else if (K == 4 * N - 3) cout << 2 * N - 1 << "\n";
        else {
            cout << (K + 1) / 2 << "\n";
        }
    }
}
