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

typedef long long ll;

unordered_map<ll, pair<ll, int>> cache[10];

pair<ll, int> consume(ll n, int mind) {
    if (cache[mind].count(n) > 0) {
        return cache[mind][n];
    }
    ll cost = 0;
    int rem;
    if (n == 0) {
        cost = 1;
        rem = -mind;
    } else {
        int d = 0;
        ll ntmp = n;
        ll p10 = 1;
        ll sub = 0;
        while (true) {
            d = ntmp % 10;
            ntmp /= 10;
            if (ntmp == 0) break;
            sub += p10 * d;
            p10 *= 10;
        }

        if (p10 == 1) {
            cost += 1;
            rem = d - max(d, mind);
            if (rem >= 0) {
                cost += 1;
                rem -= mind;
            }
        } else {
            while (d >= 0) {
                auto subcost = consume(sub, max(mind, d));
                cost += subcost.first;
                d -= 1;
                sub = p10 + subcost.second;
            }
            rem = (int)(sub - p10);
        }
    }
    // cout << n << " takes " << cost << " subtractions to reach " << rem
    //     << " (base minimum " << mind << ")" << endl;
    cache[mind][n] = {cost, rem};
    return {cost, rem};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    cout << consume(n, 0).first - 1 << endl;
}
