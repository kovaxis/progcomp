#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int N, splits, merges;
vector<vector<int>> a;
// {num, tower_idx}
vector<pair<int, int>> b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) {
        int K;
        cin >> K;
        a[i].resize(K);
        rep(k, K) cin >> a[i][k];
    }

    // split on inversion
    invrep(i, N) {
        invrepx(k, 1, a[i].size()) {
            if (a[i][k - 1] > a[i][k]) {
                cerr << "splitting tower " << i + 1 << " at " << a[i][k] << endl;
                vector<int> newtower(a[i].begin() + k, a[i].end());
                a[i].resize(k);
                a.push_back(newtower);
                splits += 1;
            }
        }
    }
    N = a.size();

    // order blocks
    rep(i, N) for (int x : a[i]) b.push_back({x, i});
    sort(b.begin(), b.end());

    int last = -1, segments = 0;
    for (auto [x, i] : b) {
        if (last != i) {
            cerr << "found segment that starts at " << x << endl;
            segments += 1;
        }
        last = i;
    }

    splits += (segments - N);
    merges += (segments - 1);

    cout << splits << " " << merges << endl;
}
