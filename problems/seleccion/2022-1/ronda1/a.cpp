#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> T;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    T.resize(N);
    rep(i, N) cin >> T[i];

    ll x = 1ll << T[0];
    repx(i, 1, N) {
        ll y = x;
        y &= ~((1ll << T[i]) - 1);
        y |= 1ll << T[i];
        if (y <= x) y += 1ll << (T[i] + 1);
        x = y;
    }
    cout << x << endl;
}
