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
        a.resize(N);
        rep(i, N) cin >> a[i];
        if (N <= 1) {
            cout << "0\n";
            continue;
        }
        int ans = INT32_MAX;
        rep(x0, N) rep(x1, x0 + 1, N) {
            int y0 = a[x0], y1 = a[x1];
            int dx = x1 - x0, dy = y1 - y0;
            int cost = 0;
            rep(x, N) cost += !(dx * a[x] == dy * (x - x0) + y0 * dx);
            ans = min(ans, cost);
        }
        cout << ans << "\n";
    }
}
