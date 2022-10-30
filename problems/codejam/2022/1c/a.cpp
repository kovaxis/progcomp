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
    rep(tc, TC) {
        cout << "Case #" << tc + 1 << ": ";

        int N;
        cin >> N;
        vector<string> S(N);
        rep(i, N) cin >> S[i];

        vector<char> ff(N), ll(N);
        rep(i, N) ff[i] = S[i][0];
        rep(i, N) ll[i] = S[i][S[i].size() - 1];

        vector<int> nxt(N, -1), prv(N, -1);
        rep(c, 128) {
            int j = -1;
            rep(i, N) {
                if (nxt[i] != -1) continue;
                if (ff[i] != c && ll[i] == c) j = i;
            }
            if (j == -1) {
                rep(i, N) {
                    if (nxt[i] != -1) continue;
                    if (ll[i] == c) j = i;
                }
            }
            if (j == -1) continue;
            int last = j;
            rep(i, N) {
                if (i == j) continue;
                if (ff[i] != ll[i] || ff[i] != c) continue;
                if (prv[i] != -1 || nxt[i] != -1) continue;
                nxt[last] = i, prv[i] = last;
                last = i;
            }
            rep(i, N) {
                if (ff[i] != c || ll[i] == c) continue;
                if (prv[i] != -1) continue;
                nxt[last] = i, prv[i] = last;
                break;
            }
        }

        // rep(i, N) cerr << "nxt[" << i << "] = " << nxt[i] << endl;

        string ans;
        vector<bool> used(N, false);
        int usedn = 0;
        bool ok = true;
        while (usedn < N) {
            int j = -1;
            rep(i, N) if (!used[i] && prv[i] == -1) j = i;
            if (j == -1) {
                ok = false;
                break;
            }
            while (true) {
                ans += S[j];
                used[j] = true;
                usedn += 1;
                j = nxt[j];
                if (j == -1) break;
                if (used[j]) {
                    ok = false;
                    usedn = N;
                    break;
                }
            }
        }
        vector<bool> usedc(128);
        int j = 0;
        while (j < ans.size()) {
            char c = ans[j++];
            if (usedc[c]) ok = false;
            while (j < ans.size() && ans[j] == c) j += 1;
            usedc[c] = true;
        }
        if (ok)
            cout << ans << "\n";
        else
            cout << "IMPOSSIBLE\n";
    }
}
