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

int N, K;
vector<int> depot[2];
ll dcost[2];
ll dextra[2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        rep(k, 2) depot[k].clear();
        cin >> N >> K;
        rep(i, N) {
            int x;
            cin >> x;
            depot[x < 0].push_back(abs(x));
        }

        rep(k, 2) {
            sort(depot[k].begin(), depot[k].end());
            int n = depot[k].size(), i = n;
            ll cost = 0, extra = 0;
            while (i > 0) {
                cost += depot[k][i - 1];
                if (i < n)
                    cost += depot[k][i - 1];
                else
                    extra = depot[k][i - 1];
                i -= K;
            }
            dcost[k] = cost;
            dextra[k] = extra;
        }

        ll ans = dcost[0] + dcost[1] + min(dextra[0], dextra[1]);
        cout << ans << "\n";
    }
}
