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

struct Seg {
    int l, r, c;
};

int N;
vector<Seg> segs;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        segs.resize(N);
        rep(i, N) {
            Seg& s = segs[i];
            cin >> s.l >> s.r >> s.c;
        }

        int mn = 0, mx = 0, sn = 0;
        rep(i, N) {
            int l = segs[i].l, r = segs[i].r, c = segs[i].c;
            if (l < segs[mn].l || (l <= segs[mn].l && c < segs[mn].c)) mn = i;
            if (r > segs[mx].r || (r >= segs[mx].r && c < segs[mx].c)) mx = i;
            if (l <= segs[sn].l && r >= segs[sn].r &&
                (l < segs[sn].l || r > segs[sn].r || c < segs[sn].c))
                sn = i;

            int cost = segs[mn].c + segs[mx].c;
            if (segs[sn].l <= segs[mn].l && segs[sn].r >= segs[mx].r)
                cost = min(cost, segs[sn].c);
            cout << cost << "\n";
        }
    }
}
