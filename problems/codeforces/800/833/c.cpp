#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int N;
vector<ll> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        ll ans = 0, l, acc = 0;
        for (l = 0; l < N; l++) {
            if (a[l] == 0) break;
            acc += a[l];
            ans += (acc == 0);
        }

        while (l < N) {
            int r = l + 1;
            while (r < N && a[r] != 0) r += 1;
            cerr << "checking range [" << l + 1 << ", " << r << "]" << endl;

            map<ll, int> cnt;
            ll acc = 0;
            repx(i, l, r) {
                acc += a[i];
                cnt[acc] += 1;
            }
            int maxcnt = 0;
            for (auto [num, c] : cnt)
                maxcnt = max(maxcnt, c);
            ans += maxcnt;

            for (auto [num, c] : cnt) cerr << "  acc " << num << " has " << c << " ocurrences" << endl;

            l = r;
        }

        cout << ans << "\n";
    }
}
