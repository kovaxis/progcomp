#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, Qn;
string S;
vector<int> cnt[26];

bool solve(int L, int R) {
    if (R - L <= 1) return true;

    if (S[L] != S[R - 1]) return true;

    int d = 0;
    rep(c, 26) d += (cnt[c][R] - cnt[c][L] != 0);

    return d >= 3;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> S;
    N = S.size();
    rep(i, N) S[i] -= 'a';

    rep(c, 26) {
        cnt[c].resize(N + 1);
        rep(i, N) cnt[c][i + 1] = cnt[c][i] + (S[i] == c);
    }

    cin >> Qn;
    rep(qi, Qn) {
        int l, r;
        cin >> l >> r;
        l--;
        cout << (solve(l, r) ? "Yes" : "No") << "\n";
    }
}
