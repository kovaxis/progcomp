#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int N;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.assign(N + 1, 0);
        rep(i, N) cin >> a[i + 1];
        rep(i, N) a[i + 1] ^= a[i];
        N += 1;
        sort(a.begin(), a.end());
        int ans = 0;
        rep(i, N - 1) {
            int gl = i + 1, gr = N - 1;
            invrep(b, 32) {
                int l = gl, r = gr + 1;
                while (l != r) {
                    int m = l + (r - l) / 2;
                    if (!(a[m] & (1 << b))) {
                        l = m + 1;
                    } else {
                        r = m;
                    }
                }
                int obj = (~a[i]) & (1 << b);
                int nl = (obj ? l : gl), nr = (obj ? gr : l - 1);
                if (nl <= nr) gl = nl, gr = nr;
            }
            ans = max(ans, a[gl] ^ a[i]);
        }
        cout << ans << '\n';
    }
}
