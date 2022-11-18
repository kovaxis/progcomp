#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> a, b;

int no_rearrange() {
    int ans = 0;
    rep(i, N) ans += (a[i] != b[i]);
    return ans;
}

int rearrange() {
    int an = 0;
    rep(i, N) an += a[i];
    int bn = 0;
    rep(i, N) bn += b[i];

    return abs(an - bn) + 1;
}

int solve() {
    return min(no_rearrange(), rearrange());
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
        b.resize(N);
        rep(i, N) cin >> b[i];

        cout << solve() << "\n";
    }
}
