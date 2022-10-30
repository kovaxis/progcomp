#include <bits/stdc++.h>
using namespace std;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) for (int i = 0; i < n; i++)
typedef long long ll;

int main() {
    string s;
    cin >> s;
    string ans = "";
    int n = s.length() / 3;
    rep(i, n) {
        if (s[i] == s[i + n])
            ans += s[i];
        else if (s[i] == s[i + 2 * n])
            ans += s[i];
        else if (s[i + n] == s[i + 2 * n])
            ans += s[i + n];
    }
    cout << ans << "\n";

    return 0;
}