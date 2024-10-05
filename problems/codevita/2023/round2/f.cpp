#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int H;
int A[5];

vector<bool> can;
vector<int> usage[5];

const bool dosort = true;
const int opt = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> H;
    rep(k, 5) cin >> A[k];

    can.assign(H + 1, false);
    rep(k, 5) usage[k].assign(H + 1, 0);

    can[0] = true;

    // TODO: try sorting the blocks
    if (dosort) {
        sort(&A[0], &A[5]);
    }

    // NOTE: how do we choose which block to use?

    if (opt == 1) {
        // option 1:
        rep(h, H + 1) {
            // TODO: try invrep
            rep(k, 5) {
                if (h - A[k] >= 0 && can[h - A[k]]) {
                    can[h] = true;
                    rep(k2, 5) usage[k2][h] = usage[k2][h - A[k]];
                    usage[k][h] += 1;
                    break;
                }
            }
        }
    } else if (opt == 2) {
        // option 2:
        rep(h, H + 1) {
            if (can[h]) {
                rep(k, 5) {
                    // TODO: try last instead of first
                    if (h + A[k] <= H && !can[h + A[k]]) {
                        can[h + A[k]] = true;
                        rep(k2, 5) usage[k2][h + A[k]] = usage[k2][h];
                        usage[k][h + A[k]] += 1;
                        break;
                    }
                }
            }
        }
    }

    if (can[H]) {
        vector<pair<int, int>> bricks(5);
        rep(k, 5) bricks[k].first = -usage[k][H];
        rep(k, 5) bricks[k].second = A[k];
        sort(bricks.begin(), bricks.end());
        bool first = true;
        for (auto b : bricks) {
            int u = b.first;
            int dh = b.second;
            if (u != 0) {
                if (first) first = false;
                else cout << " ";
                cout << dh;
            }
        }
        cout << endl;
    } else {
        cout << "Impossible" << endl;
    }
}
