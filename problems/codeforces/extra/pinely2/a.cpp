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
        int N, A, Q;
        cin >> N >> A >> Q;
        int best = A, worst = A, cur = A;
        rep(i, Q) {
            char c;
            cin >> c;
            int d = (c == '+' ? 1 : -1);
            cur += d;
            if (d > 0) best += d;
            worst = max(worst, cur);
        }

        if (worst >= N) {
            cout << "YES\n";
        } else if (best >= N) {
            cout << "MAYBE\n";
        } else {
            cout << "NO\n";
        }
    }
}
