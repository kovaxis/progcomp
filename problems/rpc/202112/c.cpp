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

int W, H;
vector<int> rows;
vector<vector<int>> rowcans;
int ans = 1e9;

vector<vector<ll>> dp;
ll search(int y, int overcans) {
    if (y < 0) return 0;
    if (dp[y][overcans] != -1) return dp[y][overcans];

    int row = rows[y];
    vector<bool> searched(1 << W, false);
    vector<int> f(__builtin_popcount(overcans), -1);
    ll count = 1e9;
    while (true) {
        int x = overcans;
        int b = 0;
        int j = 0;
        while (x != 0) {
            int z0 = __builtin_ctz(x), z = z0 + f[j];
            if (z < 0 || z >= W) {
                j = -1;
                break;
            }
            b |= 1 << z;
            x &= ~(1 << z0);
            j += 1;
        }

        if (j != -1 && !((b >> 1) & b)) {
            // cerr << "checking support cans " << bitset<12>(b)
            //     << " for y = " << y << endl;
            // search bitmask b
            for (int m : rowcans[y]) {
                int cans = b | m;
                if (searched[cans]) continue;
                searched[cans] = true;
                if ((cans >> 1) & cans) continue;
                // cerr << "checking cans " << bitset<12>(cans) << " for y = "
                // << y
                //     << endl;
                count =
                    min(count, __builtin_popcount(cans) + search(y - 1, cans));
            }
        }

        int i = 0;
        while (i < f.size()) {
            f[i] += 1;
            if (f[i] > 1)
                f[i++] = -1;
            else
                break;
        }
        if (i == f.size()) break;
    }
    return dp[y][overcans] = count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> H >> W;
    H /= 2;
    rows.resize(H);
    invrep(y, 2 * H) rep(x, W) {
        char c;
        cin >> c;
        if (c == '#') rows[y / 2] |= 1 << x;
    }

    rowcans.resize(H);
    rep(y, H) {
        vector<bool> seen(1 << W, false);
        int row = rows[y];
        // cerr << "row " << y << " = " << bitset<12>(row) << endl;
        bool first = true;
        for (int m = row;; m = (m - 1) & row) {
            if (m == row) {
                if (!first) break;
                first = false;
            }
            int cans = 0;
            cans |= m;
            cans |= ((~m) & row) << 1;
            if (cans & (1 | (1 << W))) continue;
            if (seen[cans]) continue;
            seen[cans] = true;
            if ((cans >> 1) & cans) continue;
            // cerr << "  y = " << y << " has cans " << bitset<12>(cans) <<
            // endl;
            rowcans[y].push_back(cans);
        }
    }

    dp.assign(H, vector<ll>(1 << W, -1));
    cout << search(H - 1, 0) << endl;
}
