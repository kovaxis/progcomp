#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int fact(int n) {
    int x = 1;
    repx(i, 1, n + 1) x *= i;
    return x;
}

int choose(int n, int k) {
    return fact(n) / fact(k) / fact(n - k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        rep(i, N) {
            int x;
            cin >> x;
        }

        N = 10 - N;
        // N choose 2 * 4 choose 2
        cout << choose(N, 2) * choose(4, 2) << "\n";
    }
}
