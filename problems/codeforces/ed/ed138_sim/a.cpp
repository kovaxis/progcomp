#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
vector<pair<int, int>> rooks;

// check if there is a free cell that (ox, oy) can move into.
bool check(int ox, int oy) {
    rep(x, N) rep(y, N) {
        // is cell different from original?
        if (x == ox && y == oy) continue;
        // can original move here?
        if (ox != x && oy != y) continue;
        // is cell non-attacked?
        bool free = true;
        rep(i, M) if (rooks[i].first == x || rooks[i].second == y) free = false;
        if (!free) continue;
        // ok
        return true;
    }
    return false;
}

bool solve() {
    rep(i, M) {
        M -= 1;
        swap(rooks[i], rooks[M]);
        if (check(rooks[M].first, rooks[M].second)) return true;
        swap(rooks[i], rooks[M]);
        M += 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        rooks.resize(M);
        rep(i, M) {
            int x, y;
            cin >> x >> y;
            rooks[i] = {x - 1, y - 1};
        }

        cout << (solve() ? "YES\n" : "NO\n");
    }
}
