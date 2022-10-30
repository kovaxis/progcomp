#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> a;
vector<pair<int, int>> ops;

void op(int i, int j) {
    ops.push_back({i + 1, j + 1});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ops.clear();
        cin >> N;
        a.resize(N);
        rep(i, N) {
            cin >> a[i];
            a[i] &= 1;
        }

        int k = a[0];
        int last;
        rep(i, N) if (a[i] == k) last = i;
        rep(i, N) if (a[i] == k && i != last) op(i, last);
        rep(i, N) if (a[i] != k) op(0, i);

        cout << ops.size() << "\n";
        for (auto [l, r] : ops) cout << l << " " << r << "\n";
    }
}
