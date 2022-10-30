#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll N;
    string a, b;
    cin >> N;
    cin >> a >> b;

    ll eqrow = 0;
    ll ans = 0;
    rep(i, N) {
        if (a[i] == b[i]) {
            eqrow += 1;
            continue;
        }
        if (a[i] < b[i]) {
            ans += (eqrow + 1) * (N - i);
        }
        eqrow = 0;
    }

    cout << ans << endl;
}