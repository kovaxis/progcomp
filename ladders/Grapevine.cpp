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

int h, w;
int hs[509 * 509];
pair<int, int> bounds[509 * 10009];
pair<int, int> queries_l[10009];
pair<int, int> queries_u[10009];

int largest(int q) {
    int maxside = 0;
    rep(y, h) {
        int ui = bounds[q * h + y].second;
        rep(j, maxside, y + 1) {
            // Side j+1
            int seglen = ui - bounds[q * h + y - j].first;
            if (seglen >= j + 1) {
                maxside = j + 1;
            } else {
                break;
            }
        }
    }
    return maxside;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        cin >> h >> w;
        if (h == 0 || w == 0) {
            break;
        }
        rep(y, h) {
            rep(x, w) {
                int h;
                cin >> h;
                hs[y * w + x] = h;
            }
        }
        int qs;
        cin >> qs;
        rep(q, qs) {
            int l, u;
            cin >> l >> u;
            queries_l[q] = {l, q};
            queries_u[q] = {u, q};
        }
        sort(&queries_l[0], &queries_l[qs]);
        sort(&queries_u[0], &queries_u[qs]);
        rep(y, h) {
            int x = 0;
            rep(i, qs) {
                int he = queries_l[i].first;
                int idx = queries_l[i].second;
                while (x < w && hs[y * w + x] < he) {
                    x += 1;
                }
                bounds[idx * h + y].first = x;
            }
            x = 0;
            rep(i, qs) {
                int he = queries_u[i].first;
                int idx = queries_u[i].second;
                while (x < w && hs[y * w + x] <= he) {
                    x += 1;
                }
                bounds[idx * h + y].second = x;
            }
        }
        rep(q, qs) { cout << largest(q) << '\n'; }
        cout << "-\n";
    }
}
