#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> c;

bool solve() {
    rep(i, N) if (c[i] == 1) {
        rotate(c.begin(), c.begin() + i, c.end());
        break;
    }
    if (c[0] != 1) return false;
    repx(i, 1, N) if (c[i] < 2 || c[i] > c[i - 1] + 1) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        c.resize(N);
        rep(i, N) cin >> c[i];
        cout << (solve() ? "YES\n" : "NO\n");
    }
}
