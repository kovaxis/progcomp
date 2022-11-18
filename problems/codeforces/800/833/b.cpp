#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> s;
        N = s.size();

        ll ans = 0;
        rep(l, N) {
            int cnt[10], mxcnt = 0, diff = 0;
            rep(k, 10) cnt[k] = 0;
            repx(r, l + 1, min(N + 1, l + 103)) {
                int c = s[r - 1] - '0';
                if (cnt[c] == 0) diff += 1;
                cnt[c] += 1;
                mxcnt = max(mxcnt, cnt[c]);
                // cerr << "substr " << s.substr(l, r - l) << " diverse: " << (mxcnt <= diff) << endl;
                if (mxcnt <= diff) ans += 1;
            }
        }

        cout << ans << "\n";
    }
}
