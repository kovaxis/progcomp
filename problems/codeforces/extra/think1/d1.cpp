#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
string S;

ll f(int l, int r) {
    int f = 0;
    int last = -100;
    repx(i, l, r) {
        if (S[i] == '1') {
            if (abs(i - last) > 1) {
                last = i + 1;
                f += 1;
            }
        }
    }
    return f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> S;
        ll ans = 0;
        rep(l, N) repx(r, l + 1, N + 1) ans += f(l, r);
        cout << ans << "\n";
    }
}
