#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
string s;

int solve() {
    int i = 0;
    while (i < N && s[i] == '0') i += 1;
    while (i < N && s[i] == '1') i += 1;
    int ans = 0;
    while (i < N) {
        char b = s[i];
        while (i < N && s[i] == b) i += 1;
        ans += 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        cin >> s;
        cout << solve() << "\n";
    }
}
