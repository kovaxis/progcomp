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

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        string s;
        cin >> s;
        bool ok = true;
        if (N % 3 == 2) ok = false;
        rep(i, N) {
            if (i % 3 == 2 && s[i] != s[i - 1]) ok = false;
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
}
