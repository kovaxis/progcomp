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
    rep(tc, T) {
        while (true) {
            cout << "10000000" << endl;
            int x;
            cin >> x;
            if (x == 0) break;
            if (x == -1) return 0;
            if (x > 4) {
                cout << "11111111" << endl;
                cin >> x;
                if (x == 0) break;
                if (x == -1) return 0;
            }
        }
    }
}
