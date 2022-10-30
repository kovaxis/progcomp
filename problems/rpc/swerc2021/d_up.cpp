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

    int T;
    cin >> T;
    while (T--) {
        string adn[2];
        rep(k, 2) {
            string r, s;
            int b = 0;
            cin >> r;
            for (char c : r) {
                if (c != 'B') {
                    if (s.size() && s[s.size() - 1] == c) {
                        s.pop_back();
                        continue;
                    }
                    s += c;
                    continue;
                }
                b += 1;
            }
            if (b % 2) s += 'B';
            adn[k] = s;
        }
        if (adn[0] == adn[1]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}