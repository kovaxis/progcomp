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

ll N[2], K;

// vert, horz
struct Direction {
    vector<int> ppl;
    map<int, vector<int>> strs;
} dirs[2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        rep(l, 2) cin >> N[l];
        cin >> K;
        rep(l, 2) dirs[l] = {};
        rep(l, 2) rep(i, N[l]) {
            int x;
            cin >> x;
            dirs[l].strs.insert({x, {}});
        }
        rep(k, K) {
            int pos[2];
            cin >> pos[0] >> pos[1];
            rep(l, 2) if (dirs[l].strs.count(pos[l])) {
                dirs[l].strs[pos[l]].push_back(pos[!l]);
                dirs[l].ppl.push_back(pos[!l]);
            }
        }
        rep(l, 2) {
            sort(dirs[l].ppl.begin(), dirs[l].ppl.end());
            for (auto& s : dirs[l].strs) sort(s.second.begin(), s.second.end());
        }
        ll pairs = 0;
        rep(l, 2) for (auto& duo : dirs[l].strs) {
            int x = duo.first;
            auto& str = duo.second;
            for (int y : str) {
                int y0 = (--dirs[!l].strs.upper_bound(y))->first;
                int y1 = dirs[!l].strs.lower_bound(y)->first;
                auto full0 =
                    upper_bound(dirs[l].ppl.begin(), dirs[l].ppl.end(), y0);
                auto full1 =
                    lower_bound(dirs[l].ppl.begin(), dirs[l].ppl.end(), y1);
                auto str0 = upper_bound(str.begin(), str.end(), y0);
                auto str1 = lower_bound(str.begin(), str.end(), y1);
                int xt = x, yt = y;
                if (l) swap(xt, yt);
                pairs += max(0, full1 - full0) - max(0, str1 - str0);
            }
        }
        cout << pairs / 2 << "\n";
    }
}
