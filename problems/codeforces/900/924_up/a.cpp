#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

bool solve(ll a, ll b) {
    if (a % 2 == 0 && a / 2 != b) return true;
    if (b % 2 == 0 && b / 2 != a) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ll a, b;
        cin >> a >> b;
        cout << (solve(a, b) ? "Yes" : "No") << "\n";
    }
}
