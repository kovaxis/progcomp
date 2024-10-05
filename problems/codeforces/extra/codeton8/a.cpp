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
        if (K == 1) {
            rep(i, N) cout << i + 1 << " ";
            cout << "\n";
        } else if (K == N) {
            rep(i, N) cout << "1 ";
            cout << "\n";
        } else {
            cout << "-1\n";
        }
    }
}
