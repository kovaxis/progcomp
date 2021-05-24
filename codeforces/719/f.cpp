#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int zcache[200009];
vector<int> queries;

int zeros(int up_to) {
    if (zcache[up_to] != 0) {
        return zcache[up_to] - 1;
    }
    int ones;
    cout << "? 1 " << (up_to + 1) << endl;
    cin >> ones;
    int z = up_to + 1 - ones;
    zcache[up_to] = z + 1;
    queries.push_back(up_to);
    return z;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);

    int n, ts;
    cin >> n >> ts;
    rep(t, ts) {
        int k;
        cin >> k;

        int f = 0;
        int c = n;
        while (c > 0) {
            int step = c / 2;
            int z = zeros(f + step);
            if (z < k) {
                f = f + step + 1;
                c -= step + 1;
            } else {
                c = step;
            }
        }

        for (int idx : queries) {
            if (idx >= f) {
                zcache[idx] -= 1;
                // cout << "updated [1, " << (idx + 1) << "] query to "
                //     << (zcache[idx] - 1) << " zeroes" << endl;
            }
        }

        cout << "! " << (f + 1) << endl;
    }
}
