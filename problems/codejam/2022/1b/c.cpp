#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

typedef uint8_t u8;
const int INF = 1e9;

vector<u8> allops;
vector<u8> ops[9];
u8 masktoidx[256];

u8 rot(u8 x, int n) {
    if (n == 0) return x;
    return (x << n) | (x >> (8 - n));
}

void build_canreach(int cnt, int canbe, u8 op, int canreach[9]) {
    rep(k, 9) canreach[k] = 0;
    rep(i, 10) if ((canbe >> i) & 1) {
        u8 cur = ops[cnt][i];
        rep(k, 8) {
            u8 nxt = cur ^ rot(op, k);
            canreach[__builtin_popcount(nxt)] |= 1 << (masktoidx[nxt]);
        }
    }
}

// depth, nextop
pair<int, u8> dp[9][1024];

pair<int, u8> explore(int cnt, int canbe) {
    // cerr << "exploring " << cnt << ", " << canbe << endl;
    if (canbe == 0) return {0, -1};
    if (cnt == 0) return {0, -1};
    if (dp[cnt][canbe].first != -1) return dp[cnt][canbe];
    dp[cnt][canbe] = {INF, -1};
    int mindepth = INF, minop = -1;
    for (u8 op : allops) {
        int canreach[9];
        build_canreach(cnt, canbe, op, canreach);
        int depth = 0;
        rep(k, 9) { depth = max(depth, explore(k, canreach[k]).first); }
        // cerr << "op " << op << " on state " << cnt << ", " << canbe
        //     << " finishes in " << depth << " turns" << endl;
        if (depth < mindepth) mindepth = depth, minop = op;
    }
    dp[cnt][canbe] = {-1, -1};
    return {mindepth + 1, minop};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    rep(o, 256) {
        int k = __builtin_popcount(o);
        bool found = false;
        rep(i, ops[k].size()) rep(l, 8) {
            if (rot(o, l) == ops[k][i]) {
                found = true;
                masktoidx[o] = i;
            }
        }
        if (found) continue;
        masktoidx[o] = ops[k].size();
        ops[k].push_back(o);
        allops.push_back(o);
    }

    cerr << allops.size() << endl;
    rep(k, 9) { cerr << "[" << k << "] = " << ops[k].size() << endl; }

    rep(cnt, 9) rep(canbe, 1024) dp[cnt][canbe] = {-1, -1};

    cout << "00000000" << endl;
    int k;
    cin >> k;
    int canbe = (1 << ops[k].size()) - 1;
    while (k != 0) {
        u8 op = explore(k, canbe).second;
        int canreach[9];
        build_canreach(k, canbe, op, canreach);
        rep(i, 8) cout << "01"[(op >> i) & 1];
        cout << endl;
        cin >> k;
        canbe = canreach[k];
    }
}
