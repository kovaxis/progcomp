#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; (i)-- > 0;)
#define invrep(i, n) invrepx(i, 0, n)

struct St {
    int neut() { return 0; }
    int merge(int x, int y) { return x + y; }

    int n;
    vector<int> a;
    St(int n = 0) : n(n), a(2 * n, neut()) {}

    int query(int l, int r) {
        int x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, int x) {
        for (a[i += n] = x; i /= 2;)
            a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};

struct Ev {
    int l, r;
};

int R, C;
vector<vector<bool>> rt, dn, dg;
ll ans;

void solve() {
    // tower[j] = height of tower at j
    vector<int> tower(C);
    // slant[j] = length of slant starting at j - j
    // slant[j] = real_slant[j] - j
    vector<int> slant(C), newslant(C);
    // slant[j] = last point to the right connected to j
    vector<int> end_of_seg(C);
    // slants greater than the sweepline
    St greater(C);

    vector<vector<Ev>> evs(C);

    rep(i, R) {
        // calculate end_of_seg for row
        for (int j_start = 0; j_start < C;) {
            int j_end = j_start;
            while (rt[i][j_end]) j_end += 1;
            repx(j, j_start, j_end + 1) end_of_seg[j] = j_end;
            j_start = j_end + 1;
        }

        // clear segment tree
        greater.a.assign(greater.a.size(), 0);

        // sweepline over towers and slants
        rep(j, C) {
            // start counting k at t <= slant[k]
            assert(slant[j] + C - 1 >= 0 && slant[j] + C - 1 < C);
            evs[slant[j] + C - 1].push_back({j, -1});
        }
        rep(j, C) {
            // count (real_slant[k] >= k - j) (j + 1 <= k <= min(j + tower[j], end_of_seg[j]))
            // count (slant[k] >= -j) (j + 1 <= k < min(j + tower[j], end_of_seg[j]) + 1)
            assert(-j + C - 1 >= 0 && -j + C - 1 < C);
            evs[-j + C - 1].push_back({j + 1, min(j + tower[j], end_of_seg[j]) + 1});
        }

        // execute sweepline
        invrep(i, C) {
            for (Ev ev : evs[i]) {
                if (ev.r == -1) {
                    // add slant to segtree
                    greater.update(ev.l, 1);
                } else {
                    // count slants
                    ans += greater.query(ev.l, ev.r);
                }
            }
            evs[i].clear();
        }

        // calculate tower for next row
        rep(j, C) {
            tower[j] = (dn[i][j] ? tower[j] + 1 : 0);
        }

        // calculate slant for next row
        newslant[0] = 0;
        rep(j, C - 1) {
            newslant[j + 1] = (dg[i][j] ? (slant[j] + j) + 1 : 0) - (j + 1);
        }
        swap(slant, newslant);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C;
    string line;
    getline(cin, line);

    rt.assign(R, vector<bool>(R + C));
    dn.assign(R, vector<bool>(R + C));
    dg.assign(R, vector<bool>(R + C));

    rep(i_line, 2 * R - 1) {
        getline(cin, line);
        line.resize(2 * C, ' ');
        if (i_line % 2 == 0) {
            // horizontal
            int i = i_line / 2;
            rep(j, R + C) {
                int jj = 4 * j + 2 - 2 * i;
                if (jj >= 0 && jj < 2 * C) rt[i][j] = (line[jj] != ' ');
            }
        } else {
            int i = i_line / 2;
            // vertical
            rep(j, R + C) {
                int jj = 4 * j - 1 - 2 * i;
                if (jj >= 0 && jj < 2 * C) dn[i][j] = (line[jj] != ' ');
            }
            // diagonal-right
            rep(j, R + C) {
                int jj = 4 * j + 1 - 2 * i;
                if (jj >= 0 && jj < 2 * C) dg[i][j] = (line[jj] != ' ');
            }
        }
    }
    C = R + C;

    cerr << "read input" << endl;

    solve();
    cerr << "solved up" << endl;

    // reverse triangles and count again
    reverse(rt.begin(), rt.end());
    for (auto &row : rt) reverse(row.begin(), --row.end());
    reverse(dn.begin(), --dn.end());
    for (auto &row : dn) reverse(row.begin(), row.end());
    reverse(dg.begin(), --dg.end());
    for (auto &row : dg) reverse(row.begin(), --row.end());

    solve();
    cerr << "solved down" << endl;

    cout << ans << endl;
}