// incomplete

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

int N, M, A, B, C;
string s;
vector<int> nxt, prv, sz;
priority_queue<pair<int, int>> smalls[2];
set<int> singles;

ll solve(int nxtop) {
    {
        sz.clear();
        sz.push_back(0);
        if (s[0] == '0') sz.push_back(0);
        int i = 0;
        while (i < N) {
            int o = i;
            while (i < N && s[o] == s[i]) i++;
            sz.push_back(i - o);
        }
        sz.push_back(0);
    }
    M = sz.size();
    nxt.resize(M), prv.resize(M);
    rep(i, M) nxt[i] = i + 1, prv[i] = i - 1;

    smalls = {};
    ones.clear();
    rep(i, M) if (sz[i] == 1 && i % 2 == 0) ones.insert(i);
    rep(i, M) if (sz[i] > 1) smalls[i % 2].push({sz[i], i});

    ll profit = 0;
    while (true) {
        if (nxtop) {
            // remove 0
            if (smalls[1].empty() || smalls[0].empty()) {
                // remove single 0

            } else {
                // shrink 0 group
                int i = smalls[0].pop().second;
                sz[i] -= 1;
                profit += A;
                if (sz[i] == 1)
                    singles.insert(i);
                else
                    smalls[0].push({sz[i], i});
            }
        } else {
            // remove 1
        }
        nxtop = !nxtop;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    string tmps;
    while (T--) {
        cin >> N >> A >> B >> C >> tmps;
        s = tmps;
        ll ans = solve(0);
        s = tmps;
        ans = max(ans, solve(1));
        cout << ans << "\n";
    }
}
