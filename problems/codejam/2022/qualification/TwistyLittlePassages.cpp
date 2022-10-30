#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        ll N, K;
        cin >> N >> K;
        ll r0, p0;
        cin >> r0 >> p0;
        vector<int> nodes(N);
        rep(i, N) nodes[i] = i;
        shuffle(nodes.begin(), nodes.end(), rng);
        double total = 0;
        K = min(N, K);
        rep(i, K) {
            ll x;
            cout << "T " << nodes[i] + 1 << endl;
            cin >> r0 >> x;
            total += x;
        }
        double est = total / K * N / 2;
        ll esti = est + 0.5;
        cout << "E " << esti << endl;
    }
}
