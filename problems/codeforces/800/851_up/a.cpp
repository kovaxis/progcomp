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
        vector<int> a(N);
        rep(i, N) cin >> a[i];

        int cnt = 0;
        rep(i, N) cnt += a[i] == 2;

        if (cnt % 2 == 1) {
            cout << "-1\n";
            continue;
        }

        if (cnt == 0) {
            cout << "1\n";
            continue;
        }

        int target = cnt / 2;
        rep(i, N) {
            if (a[i] == 1) continue;
            cnt -= 1;
            if (cnt == target) {
                cout << i + 1 << "\n";
                break;
            }
        }
    }
}
