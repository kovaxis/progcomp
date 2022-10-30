#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int N;
vector<int> die;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        die.resize(N);
        rep(i, N) cin >> die[i];

        sort(die.begin(), die.end());
        int ans = 0, nxt = 1;
        rep(i, N) {
            if (die[i] >= nxt) {
                ans += 1;
                nxt += 1;
            }
        }

        cout << "Case #" << t + 1 << ": " << ans << "\n";
    }
}
