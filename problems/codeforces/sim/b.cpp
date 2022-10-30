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

pair<int, int> chars[200001][2];
bool sel[200001];

pair<ll, ll> try_swap(ll bot, ll top, int i) {
    ll newbot = bot - chars[i][sel[i]].first + chars[i][!sel[i]].first;
    ll newtop = top - chars[i][sel[i]].second + chars[i][!sel[i]].second;
    return {newbot, newtop};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    rep(i, n) {
        cin >> chars[i][0].first >> chars[i][0].second >> chars[i][1].first >>
            chars[i][1].second;
    }
    ll bot = 0;
    ll top = 0;
    rep(i, n) {
        bot += chars[i][sel[i]].first;
        top += chars[i][sel[i]].second;
    }

    /*{
        double maxwin = 0.;
        int i = 0;
        while (i < n) {
            auto newpair = try_swap(bot, top, i);
            bot = newpair.first;
            top = newpair.second;
            sel[i] = !sel[i];
            if (!sel[i]) {
                i += 1;
            } else {
                double win = (double)top / (double)bot;
                maxwin = max(maxwin, win);
                i = 0;
            }
        }
        cout << "exhaustive max: " << maxwin << endl;
    }*/

    double curwin = (double)top / (double)bot;
    rep(iter, 250) {
        rep(i, n) {
            auto newpair = try_swap(bot, top, i);
            double pwin = (double)newpair.second / (double)newpair.first;
            if (pwin >= curwin) {
                sel[i] = !sel[i];
                bot = newpair.first;
                top = newpair.second;
                curwin = pwin;
            }
        }
    }
    cout << fixed << setw(10) << setprecision(10) << curwin << endl;
}
