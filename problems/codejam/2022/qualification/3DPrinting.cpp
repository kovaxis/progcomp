#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int minc[4];
int outc[4];
int totalc;
const int need = 1e6;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cout << "Case #" << t + 1 << ":";
        rep(k, 4) minc[k] = 1e9;
        rep(i, 3) {
            int c[4];
            rep(k, 4) cin >> c[k];
            rep(k, 4) minc[k] = min(minc[k], c[k]);
        }

        totalc = 0;
        rep(k, 4) {
            int add = max(min(need - totalc, minc[k]), 0);
            outc[k] = add;
            totalc += add;
        }

        if (totalc < need) {
            cout << " IMPOSSIBLE\n";
        } else {
            rep(k, 4) cout << " " << outc[k];
            cout << "\n";
        }
    }
}
