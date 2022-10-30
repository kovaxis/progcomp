#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int n, x;
int minutes[10000];

int timemod(int t) {
    if (t < 8 * 60) {
        return t;
    } else {
        return 8 * 60 + (t - 8 * 60) % x;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> x;
    vector<pair<int, int>> evs;
    rep(i, n) {
        int s, d;
        cin >> s >> d;
        evs.push_back({s, 1});
        evs.push_back({s + d + 1, 0});
    }
    sort(evs.begin(), evs.end());
    int acts = 0;
    int time = 0;
    for (auto& ev : evs) {
        while (time < ev.first) {
            minutes[timemod(time)] += acts;
            time += 1;
        }
        if (ev.second == 1) {
            // open
            acts += 1;
        } else if (ev.second == 0) {
            // close
            acts -= 1;
        }
    }
    int mincols = -1;
    int minans = 0;
    rep(ans, 8 * 60 + 1) {
        int t = ans;
        ll cols = 0;
        while (t < 8 * 60 + x) {
            cols += minutes[t];
            t += x;
        }
        if (mincols == -1 || cols < mincols) {
            mincols = cols;
            minans = ans;
        }
    }
    cout << minans << " " << mincols << endl;
}
