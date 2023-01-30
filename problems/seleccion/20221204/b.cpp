#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll solve(ll N) {
    repx(x, 2, N) {
        if (x * x > N) break;
        if (N % x == 0) {
            return N / x;
        }
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ll N;
        cin >> N;
        ll x = solve(N);
        cout << x << " " << N - x << "\n";
    }
}
