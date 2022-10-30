#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

bool solve(int N, int X, int Y) {
    if (Y != 0) swap(X, Y);
    if (Y != 0) return false;
    if (X == 0) return false;

    N -= 1;
    if (N % X != 0) return false;
    rep(i, N) {
        cout << (i / X) * X + 2 << " \n"[i == N - 1];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N, X, Y;
        cin >> N >> X >> Y;

        if (!solve(N, X, Y)) {
            cout << "-1\n";
        }
    }
}
