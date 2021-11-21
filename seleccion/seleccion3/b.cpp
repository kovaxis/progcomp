#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ox, oy;
    cin >> ox >> oy;

    int x = ox - oy, y = ox + oy;
    if (x < 0) {
        cout << "-1\n";
        return 0;
    }

    int h = y - x;
    int off = y % h;
    int steps = y / h;
    double ans = (double)h + (double)off / (double)steps;
    cout << fixed << setw(12) << setprecision(12) << 0.5 * ans << endl;
}
