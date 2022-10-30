
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

int N, K;
vector<pair<int, int>> a;
vector<int> c;

bool solve() {
    rep(i, N) if (c[a[i].second] != c[i]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    a.resize(N);
    c.resize(N);
    rep(i, N) cin >> a[i].first >> c[i];
    rep(i, N) a[i].second = i;

    sort(a.begin(), a.end());

    if (solve()) {
        cout << "Y\n";
    } else {
        cout << "N\n";
    }
}