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
// visits, index
vector<pair<int, int>> visits;
vector<int> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        visits.resize(N), ans.resize(N);
        rep(i, N) {
            int v;
            cin >> v;
            visits[i] = {v, i};
        }
        sort(visits.begin(), visits.end());
        int nxt = 1;
        ll time = 0;
        invrep(i, N) {
            int v = visits[i].first, idx = visits[i].second;
            ans[idx] = nxt;
            time += 2 * (ll)v * abs(nxt);
            nxt = -nxt;
            nxt += nxt > 0;
        }

        cout << time << "\n";
        cout << "0";
        rep(i, N) cout << " " << ans[i];
        cout << "\n";
    }
}
