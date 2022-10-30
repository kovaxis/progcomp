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

int intervals[1000000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        int n;
        cin >> n;
        char c;
        while (true) {
            cin >> c;
            if (c == '*' || c == '.') {
                break;
            }
        }
        int last = -1;
        int icount = 0;
        long long r = 0ll;
        long long acc = 0ll;
        rep(i, n) {
            if (c == '*') {
                // Sheep
                if (last != -1) {
                    intervals[icount++] = i - last - 1;
                    acc += i - last - 1;
                    r += acc;
                }
                last = i;
            } else {
                // Empty
            }
            if (i < n - 1) {
                cin >> c;
            }
        }
        long long l = 0ll;
        long long minm = 4ll * r;
        rep(i, icount) {
            minm = min(minm, l + r);
            // cout << "on interval " << i << ": " << (l + r) << endl;
            l += intervals[i] * (i + 1);
            r -= intervals[i] * (icount - i);
        }
        minm = min(minm, l + r);
        // cout << "on interval " << icount << ": " << (l + r) << endl;
        cout << minm << '\n';
    }
}
