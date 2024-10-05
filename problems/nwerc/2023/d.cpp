#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, a, b)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<string> grilla(7);

    for (int i = 0; i < 7; i++) {
        cin >> grilla[i];
    }

    int n, m;
    cin >> n >> m;

    double res = 0;

    for (int bitmask = 0; bitmask < (1 << 7); bitmask++) {
        if (__builtin_popcount(bitmask) != n) continue;
        vector<int> A(24, 0);
        for (int j = 0; j < 24; j++) {
            for (int i = 0; i < 7; i++) {
                if ((bitmask & (1 << i)) == 0) continue;
                if (grilla[i][j] == '.') {
                    A[j]++;
                }
            }
        }
        sort(A.begin(), A.end(), greater<int>());
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum = sum + A[j];
        }
        res = max(res, double(sum) / double(n * m));
    }

    cout << fixed << setprecision(15) << res << endl;
}