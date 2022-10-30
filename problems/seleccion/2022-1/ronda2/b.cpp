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

    int N;
    cin >> N;
    vector<string> s[2];
    s[0].resize(N);
    s[1].resize(N);
    rep(i, N) rep(k, 2) cin >> s[k][i];

    bool ok = true;
    rep(i, N) {
        // make sure one name is different from all other family and given names
        bool ok2 = false;
        rep(k1, 2) {
            bool ok3 = true;
            rep(j, N) if (i != j) {
                rep(k2, 2) if (s[k2][j] == s[k1][i]) ok3 = false;
            }
            if (ok3) ok2 = true;
        }
        if (!ok2) ok = false;
    }

    cout << (ok ? "Yes" : "No") << endl;
}
