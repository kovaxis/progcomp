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

const int MAXM = 20;

ll N, M;
vector<int> people;

// members, bitmask
// perms
ll dp[4][1 << MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    string ins;
    rep(t, T) {
        cin >> N >> M;
        people.resize(N);
        rep(i, N) {
            cin >> ins;
            int mask = 0;
            rep(j, M) mask |= (ins[j] == 'y') << j;
            people[i] = mask;
        }

        rep(n, 4) rep(mask, 1 << M) dp[n][mask] = 0;
        dp[0][0] = 1;

        rep(n, 3) {
            cerr << "at " << n << "people\n";
            rep(mask, 1 << M) {
                rep(i, N) {
                    int newmask = mask | people[i];
                    dp[n + 1][newmask] += dp[n][mask];
                }
            }
        }

        ll ans = dp[3][(1 << M) - 1];

        cerr << "raw: " << ans << '\n';

        {
            ll n = N;
            rep(i, N) if (people[i] == (1 << M) - 1) {
                ans -= n * n;
                ans -= (n - 1) * n;
                ans -= (n - 1) * (n - 1);
                ans += 3 * (n - 1) * (n - 2);
                n -= 1;
            }
        }

        cerr << "removed fulls: " << ans << '\n';

        rep(i, N) rep(j, i + 1, N) {
            if (people[i] == (1 << M) - 1 || people[j] == (1 << M) - 1)
                continue;
            if ((people[i] | people[j]) != (1 << M) - 1) continue;
            ans -= 6;
        }

        cerr << "removed pairs: " << ans << '\n';

        ans /= 6;

        cout << ans << '\n';
    }
}
