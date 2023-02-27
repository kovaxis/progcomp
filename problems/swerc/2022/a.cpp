#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        int N;
        cin >> N;
        vector<int> a(N + 2);
        a[0] = 0;
        a[N + 1] = 1440;
        rep(i, N) {
            cin >> a[i + 1];
        }
        int prev = 0;
        int walks = 0;
        for (int x : a) {
            int t = x - prev;
            walks += t / 120;
            prev = x;
        }
        cout << (walks >= 2 ? "YES\n" : "NO\n");
    }
}