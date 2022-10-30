#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int N;
string s, t;
int nxt[256];
int nxtsym[256];
int used;

void find_next(char c) {
    while (nxt[c] < used) nxtsym[c] += (s[nxt[c]] != 0), nxt[c] += 1;
    while (nxt[c] < N) {
        if (s[nxt[c]] == c) break;
        nxtsym[c] += (s[nxt[c]] != 0), nxt[c] += 1;
    }
}

void rotate(int i, int j) {
    s[j] = '\0';
    used = i + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(q, T) {
        cin >> N >> s >> t;
        rep(c, 'a', 'z' + 1) nxt[c] = 0, nxtsym[c] = 0;

        ll extra = 0, ans = 1e18;
        int isym = 0;
        rep(i, N) {
            if (s[i] == 0) continue;
            cerr << "checking '" << s[i] << "'" << endl;

            int nxt_lt = N;
            rep(c, 'a', t[i]) {
                find_next(c);
                nxt_lt = min(nxt_lt, nxtsym[c]);
            }
            cerr << "  next letter smaller than '" << t[i] << "' is "
                 << (nxt_lt >= N ? -1 : nxt_lt - isym) << " letters away"
                 << endl;
            if (nxt_lt < N) ans = min(ans, extra + nxt_lt - isym);

            find_next(t[i]);
            cerr << "  next letter equal to '" << t[i] << "' is at "
                 << nxt[t[i]] << ", " << nxtsym[t[i]] - isym << " letters away"
                 << endl;
            if (nxt[t[i]] >= N) break;
            extra += nxtsym[t[i]] - isym;
            cerr << "  rotating range [" << i << ", " << nxt[t[i]] << "]"
                 << endl;
            rotate(i, nxt[t[i]]);
            isym += 1;
        }
        if (ans == 1e18) ans = -1;
        cout << ans << "\n";
    }
}
