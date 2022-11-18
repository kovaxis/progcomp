#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int solve(vector<int> &a, int N) {
    int g = 0;
    rep(i, N) g = __gcd(g, a[i]);

    if (g == 1) return 0;
    if (__gcd(g, N) == 1) return 1;
    if (__gcd(g, N - 1) == 1) return 2;
    if (__gcd(__gcd(g, N), N - 1)) return 3;
    throw "unreachable";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        vector<int> a(N);
        rep(i, N) cin >> a[i];

        cout << solve(a, N) << "\n";
    }
}
