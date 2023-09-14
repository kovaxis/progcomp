#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
int ans;

int ask(int i) {
    cout << "? " << i + 1 << endl;
    int x;
    cin >> x;
    return x;
}

void solve() {
    ans = 0;
    rep(b, N / K) {
        ans ^= ask(b * K);
    }
    // if (N % K == 0) return;

    int l = (N / K - 1) * K;
    int n = (N % K) / 2;
    int ac = ask(l + n);
    int ad = ask(l + 2 * n);
    ans ^= ac ^ ad;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        solve();
        cout << "! " << ans << endl;
    }
}
