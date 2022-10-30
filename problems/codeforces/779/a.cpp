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

    int T;
    cin >> T;
    while (T--) {
        int N;
        string s;
        cin >> N >> s;
        int last = -100, ans = 0;
        rep(i, N) {
            if (s[i] == '0') {
                if (i - last == 1) ans += 2;
                if (i - last == 2) ans += 1;
                last = i;
            }
        }
        cout << ans << "\n";
    }
}
