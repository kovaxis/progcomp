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
        string s;
        cin >> s;
        int n = sqrt(s.size()) + 0.5;
        string t;
        invrep(j, n) {
            rep(i, n) {
                t += s[i * n + j];
            }
        }
        cout << t << "\n";
    }
}
