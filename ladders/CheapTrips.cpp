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

pair<int, int> trips[10009];
double costfrom[10009];

const double DISC[6] = {1., 0.5, 0.25, 0.25, 0.25, 0.25};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int dend = -1;

    cin >> n;
    rep(i, n) { cin >> trips[i].first >> trips[i].second; }
    costfrom[n] = 0;
    invrep(i, n) {
        // From trip i
        int rem = 120;
        double costacc = 0.;
        double mincost = INFINITY;
        rep(j, 6) {
            if (i + j >= n || rem <= 0) {
                break;
            }
            rem -= trips[i + j].first;
            costacc += (double)trips[i + j].second * DISC[j];
            mincost = min(mincost, costacc + costfrom[i + j + 1]);
        }
        costfrom[i] = mincost;
    }
    cout << fixed << setprecision(2) << setw(2) << costfrom[0] << '\n';
}
