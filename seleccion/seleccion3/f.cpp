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

int T, N;
// pos, cost
pair<int, int> stations[200002];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int d;
    cin >> d >> T >> N;
    rep(i, N) cin >> stations[i].first >> stations[i].second;
    stations[N++] = {0, 0};
    sort(stations, stations + N);

    // pos, cost
    vector<pair<int, int>> costcurve;
    int lastpos = d;
    invrep(i, N) {
        int pos = stations[i].first;
        int cost = stations[i].second;
        int placepos = lastpos;
        if (lastpos > pos + T) {
            cout << "-1\n";
            return 0;
        }
        while (!costcurve.empty() && costcurve.back().second > cost) {
            if (costcurve.back().first > pos + T) {
                placepos = pos + T;
                break;
            }
            placepos = costcurve.back().first;
            costcurve.pop_back();
        }
        costcurve.push_back({placepos, cost});
        // cerr << "costcurve at station " << pos << ": ";
        // for (auto refill : costcurve) {
        //    cerr << " (" << refill.first << ", " << refill.second << ")";
        // }
        // cerr << '\n';
        lastpos = pos;
    }
    ll totalcost = 0;
    lastpos = d;
    ll lastcost = 0;
    for (auto refill : costcurve) {
        int pos = refill.first;
        totalcost += (lastpos - pos) * lastcost;
        lastpos = pos;
        lastcost = refill.second;
    }
    cout << totalcost << '\n';
}
