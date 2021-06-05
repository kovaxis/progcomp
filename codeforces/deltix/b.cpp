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

int a[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        int n;
        cin >> n;
        rep(i, n) { cin >> a[i]; }
        n /= 2;
        cout << (n * 6) << '\n';
        rep(i, 1, n + 1) {
            int j = 2 * n - i + 1;
            cout << "2 " << i << " " << j << '\n';
            cout << "1 " << i << " " << j << '\n';
            cout << "1 " << i << " " << j << '\n';
            cout << "2 " << i << " " << j << '\n';
            cout << "1 " << i << " " << j << '\n';
            cout << "1 " << i << " " << j << '\n';
        }
    }
}
