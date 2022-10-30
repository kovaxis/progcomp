#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int L, R, N;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> L >> R;
        N = R - L + 1;
        a.resize(N);
        rep(i, N) cin >> a[i];
        int X = 0, unk = 0;
        rep(b, 30) {
            int ex_ones = 0;
            repx(k, L, R + 1) ex_ones += ((k >> b) & 1);

            int ones = 0;
            rep(i, N) ones += ((a[i] >> b) & 1);

            if (ones == ex_ones && N - ones != ex_ones)
                X |= 0 << b;
            else if (N - ones == ex_ones && ones != ex_ones)
                X |= 1 << b;
            else
                unk |= 1 << b;
        }
        // cerr << "X = " << X << ", unk = " << unk << endl;
        int ans = -1;
        for (int sub = unk;; sub = (sub - 1) & unk) {
            int x = X | sub;
            bool ok = true;
            rep(i, N) {
                int b = a[i] ^ x;
                if (b < L || b > R) ok = false;
            }
            if (ok) ans = x;
            if (sub == 0) break;
        }
        cout << ans << "\n";
    }
}
