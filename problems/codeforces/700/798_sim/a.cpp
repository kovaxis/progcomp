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
        int N, M, K;
        cin >> N >> M >> K;
        string s[2], c;
        cin >> s[0] >> s[1];
        rep(k, 2) sort(s[k].rbegin(), s[k].rend());
        int last = -1, cnt = 0;
        while (!s[0].empty() && !s[1].empty()) {
            int usea = s[0].back() > s[1].back();
            if (usea != last) last = usea, cnt = 0;
            if (cnt >= K) usea = !usea, last = usea, cnt = 0;
            cnt += 1;
            c.push_back(s[usea].back());
            s[usea].pop_back();
        }
        cout << c << "\n";
    }
}
