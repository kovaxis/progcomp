#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
ll R, I;
map<int, int> cnt;

ll solve() {
    ll base = 0;
    for (auto [x, c] : cnt)
        base += c * R;
    int prev = 0;
    ll ans = base + I;
    for (auto [x, _] : cnt) {
        base -= R;
        base += (x - 1 - prev) * I;
        prev = x;
        ans = min(ans, base);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> R >> I;
        cnt.clear();
        rep(i, N) {
            int x;
            cin >> x;
            cnt[x] += 1;
        }

        cout << solve() << "\n";
    }
}
