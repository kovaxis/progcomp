#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s, t;
    cin >> s >> t;

    map<char, set<int>> C;
    rep(i, s.size()) C[s[i]].insert(i);

    int i = s.size(), ans = 0;
    rep(j, t.size()) {
        char c = t[j];
        auto it = C[c].lower_bound(i);
        if (it == C[c].end()) {
            i = 0, ans++, j--;
            continue;
        }
        i = *it + 1;
    }

    cout << ans << endl;
}