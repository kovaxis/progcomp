#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

int N;
vector<pair<int, int>> kids, sweets;

ll distsq(pair<int, int> a, pair<int, int> b) {
    ll dx = (ll)a.first - b.first, dy = (ll)a.second - b.second;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cout << "Case #" << tc + 1 << ": ";

        cin >> N;
        kids.resize(N);
        rep(i, N) cin >> kids[i].first >> kids[i].second;
        sweets.resize(N + 1);
        cin >> sweets[N].first >> sweets[N].second;
        rep(i, N) cin >> sweets[i].first >> sweets[i].second;

        vector<int> p(N), go(N);
        rep(i, N) p[i] = i;
        vector<bool> got(N);

        do {
            got.assign(N + 1, false);
            for (int k : p) {
                ll mind = INF, mini = 0;
                rep(i, N + 1) {
                    if (got[i]) continue;
                    ll d = distsq(kids[k], sweets[i]);
                    if (d < mind) mind = d, mini = i;
                }
                got[mini] = true;
                go[k] = mini;
            }
            if (!got[N]) break;
        } while (next_permutation(p.begin(), p.end()));

        if (got[N]) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << "POSSIBLE\n";
            for (int k : p) {
                cout << k + 1 << " " << go[k] + 2 << "\n";
            }
        }
    }
}
