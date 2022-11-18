#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<ll> a, b;

ll lcm(int x, int y) {
    return x / __gcd(x, y) * y;
}

bool solve() {
    b.resize(N + 1);
    b[0] = a[0];
    repx(i, 1, N) {
        b[i] = lcm(a[i - 1], a[i]);
    }
    b[N] = a[N - 1];

    rep(i, N) if (__gcd(b[i], b[i + 1]) != a[i]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];
        cout << (solve() ? "YES\n" : "NO\n");
    }
}
