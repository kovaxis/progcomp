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

ll N, B, X, Y;
ll opts[2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> B >> X >> Y;
        opts[0] = X;
        opts[1] = -Y;

        ll cur = 0;
        ll ans = 0;
        rep(i, N) {
            rep(k, 2) {
                if (cur + opts[k] > B) continue;
                cur += opts[k];
                break;
            }
            ans += cur;
        }
        cout << ans << "\n";
    }
}
