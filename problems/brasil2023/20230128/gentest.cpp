#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int M, N;
    cerr << "min x y: " << flush;
    int x0, y0, x1, y1;
    cin >> x0 >> y0;
    cerr << "max x y: " << flush;
    cin >> x1 >> y1;
    cerr << "M N: " << flush;
    cin >> M >> N;
    assert(x0 >= 1 && y0 >= 1 && x1 < M && y1 < M);
    vector<pair<int, int>> a;
    repx(x, x0, x1 + 1) repx(y, y0, y1 + 1) a.push_back({x, y});
    shuffle(a.begin(), a.end(), rng);

    cout << M << " " << N << "\n";
    assert(N <= a.size());
    rep(i, N) cout << a[i].first << " " << a[i].second << "\n";
}
