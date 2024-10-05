#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

bool solve(ll K, ll X, ll A) {
    ll a = A;
    rep(x, X) {
        ll jmp = (A - a) / (K - 1) + 1;
        if (jmp >= a) return false;
        a -= jmp;
    }
    return a * K > A;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ll K, X, A;
        cin >> K >> X >> A;
        cout << (solve(K, X, A) ? "YES" : "NO") << "\n";
    }
}
