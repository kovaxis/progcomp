#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
char input[512][512];
char output[512][512];

char col(bool c) { return "BW"[c]; }

bool solve() {
    rep(i, N) rep(j, M) output[i][j] = '.';

    rep(i, N) {
        bool nxt = true;
        rep(j, M) {
            if (input[i][j] == 'U') {
                output[i][j] = col(nxt);
                output[i + 1][j] = col(!nxt);
                nxt = !nxt;
            }
        }
        if (!nxt) return false;
    }
    rep(j, M) {
        bool nxt = true;
        rep(i, N) {
            if (input[i][j] == 'L') {
                output[i][j] = col(nxt);
                output[i][j + 1] = col(!nxt);
                nxt = !nxt;
            }
        }
        if (!nxt) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        rep(i, N) rep(j, M) cin >> input[i][j];

        if (solve()) {
            rep(i, N) {
                rep(j, M) cout << output[i][j];
                cout << "\n";
            }
        } else {
            cout << "-1\n";
        }
    }
}
