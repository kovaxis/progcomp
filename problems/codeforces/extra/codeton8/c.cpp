#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, X, Y;
vector<int> A;

int solve() {
    sort(A.begin(), A.end());

    int ans = X - 2;
    rep(i, X) ans += ((A[i] + 2) % N == A[(i + 1) % X]);

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> X >> Y;
        A.resize(X);
        rep(i, X) cin >> A[i];
        rep(i, X) A[i] -= 1;
        cout << solve() << "\n";
    }
}
