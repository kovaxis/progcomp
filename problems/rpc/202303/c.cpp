#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    double n, k, d, s;
    cin >> n >> k >> d >> s;
    double ans = (n * d - k * s) / (n - k);
    if (0 <= ans && ans <= 100) {
        cout << fixed << ans << endl;
    } else {
        cout << "impossible" << endl;
    }
}