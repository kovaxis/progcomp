#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> v(11, -100000);

        rep(i, n) {
            int a, b;
            cin >> a >> b;
            v[b] = max(v[b], a);
        }
        int sum = 0;
        repx(i, 1, 11) { sum += v[i]; }
        if (sum < 0) {
            cout << "MOREPROBLEMS" << endl;
        } else
            cout << sum << endl;
    }
}