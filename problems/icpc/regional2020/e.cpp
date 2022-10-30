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

int n;
int a[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    rep(i, n) cin >> a[i];

    vector<pair<int, int>> evs;
    priority_queue<pair<int, int>> found;
    rep(i, n) {
        while (!found.empty() && -found.top().first < a[i]) {
            int j = found.top().second;
            found.pop();
            evs.push_back({(i + j + 1) / 2, -1});
        }
        found.push({-a[i], i});
    }
    while (!found.empty()) {
        evs.push_back({n, -1});
        found.pop();
    }
    invrep(i, n) {
        while (!found.empty() && -found.top().first < a[i]) {
            int j = found.top().second;
            found.pop();
            evs.push_back({(i + j + 2) / 2, 1});
        }
        found.push({-a[i], i});
    }
    while (!found.empty()) {
        evs.push_back({0, 1});
        found.pop();
    }
    sort(evs.begin(), evs.end());
    int evi = 0;
    int active = 0;
    rep(i, n) {
        while (evi < evs.size() && evs[evi].first <= i) {
            active += evs[evi].second;
            evi += 1;
        }
        cout << active - 1 << " \n"[i == n - 1];
    }
}
