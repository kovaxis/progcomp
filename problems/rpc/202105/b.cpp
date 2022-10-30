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

int sides[51];
//|a-b|, a+b
pair<int, int> pairs[51 * 51];
// including, excluding
pair<long long, long long> pointvals[51 * 51 * 2];
int decompress[51 * 51 * 2];

// val, idx
pair<int, int> points[51 * 51 * 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int pn = 0;
    rep(i, n) {
        cin >> sides[i];
        rep(j, i) {
            pair<int, int> pair = {abs(sides[i] - sides[j]),
                                   sides[i] + sides[j]};
            points[pn * 2] = {pair.first, pn};
            points[pn * 2 + 1] = {pair.second, -pn - 1};
            pairs[pn++] = pair;
        }
    }

    sort(points, points + 2 * pn);
    int cn = 0;
    int lastval = -1;
    rep(i, 2 * pn) {
        int val = points[i].first;
        if (val != lastval) {
            pointvals[cn] = {0, 0};
            decompress[cn] = val;
            cn += 1;
            lastval = val;
        }

        int idx = points[i].second;
        if (idx < 0) {
            idx = -idx - 1;
            pairs[idx].second = cn - 1;
        } else {
            pairs[idx].first = cn - 1;
        }
    }

    long long total = 0;
    int pidx = 0;
    rep(i, n) {
        int idx =
            lower_bound(decompress, decompress + cn, sides[i]) - decompress;
        if (decompress[idx] == sides[i]) {
            cout << "side " << sides[i] << " corresponds to "
                 << pointvals[idx].first << " sets" << endl;
            total += pointvals[idx].first;
        } else {
            cout << "side " << sides[i] << " corresponds to "
                 << pointvals[idx].second << " sets" << endl;
            total += pointvals[idx].second;
        }

        rep(j, i) {
            auto& pair = pairs[pidx++];
            cout << "  pair reaches (" << decompress[pair.first] << ", "
                 << decompress[pair.second] << ")" << endl;
            pointvals[pair.first].second = 2 * pointvals[pair.first].second + 1;
            cout << "    incrementing (" << decompress[pair.first] << ", inf)"
                 << pointvals[pair.first].second << endl;
            rep(k, pair.first + 1, pair.second) {
                cout << "    incrementing [" << decompress[k] << ", inf)"
                     << endl;
                pointvals[k].first = 2 * pointvals[k].first + 1;
                pointvals[k].second = 2 * pointvals[k].second + 1;
            }
        }
    }
    cout << total << '\n';
}
