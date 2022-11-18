#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<pair<int, int>> ranges;
vector<ll> a;
string lid;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        lid.resize(N);
        cin >> lid;
        a.resize(N);
        rep(i, N) cin >> a[i];

        {
            ranges.clear();
            int i = 0;
            while (i < N && lid[i] == '1') i++;
            while (i < N) {
                int start = i;
                while (true) {
                    i += 1;
                    if (i >= N) break;
                    if (lid[i] == '0') break;
                }
                if (i - start > 1)
                    ranges.push_back({start, i});
            }
        }

        ll ans = 0;
        rep(i, N) {
            if (lid[i] == '0') break;
            ans += a[i];
        }
        for (auto [l, r] : ranges) {
            ll mn = 1e18;
            repx(i, l, r) mn = min(mn, a[i]);
            ll sm = 0;
            repx(i, l, r) sm += a[i];

            ans += sm - mn;
        }

        cout << ans << "\n";
    }
}
