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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    string s;
    cin >> T;
    rep(t, T) {
        int n, a, b;
        cin >> n >> a >> b;
        cin >> s;
        if (b < 0) {
            // Group
            int groups = 0;
            int last = ' ';
            rep(i, n) {
                if (last != s[i]) groups += 1;
                last = s[i];
            }
            cout << n * a + (groups / 2 + 1) * b << '\n';
        } else {
            // Don't group
            cout << n * (a + b) << '\n';
        }
    }
}
