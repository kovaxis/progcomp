#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        int k;
        for (k = 0;; k += 1) {
            // run game with k
            b = a;
            bool win = true;
            invrepx(m, 1, k + 1) {
                // stage m
                // alice
                int mx = -1e9, mxj = -1;
                rep(j, N) if (b[j] > mx && b[j] <= m) mx = b[j], mxj = j;
                if (mxj == -1) {
                    win = false;
                    break;
                }
                b[mxj] += m;
                // bob
                int mn = 1e9, mnj = -1;
                rep(j, N) if (b[j] < mn) mn = b[j], mnj = j;
                if (mnj != -1) b[mnj] += m;
            }
            if (!win) {
                k -= 1;
                break;
            }
        }

        cout << k << "\n";
    }
}
