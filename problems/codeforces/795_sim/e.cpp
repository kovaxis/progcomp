#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Dsu {
    vector<int> p, r;

    // initialize the disjoint-set-union to all unitary sets
    void reset(int N) {
        p.resize(N), r.assign(N, 0);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two sets with leaders `i` and `j`
    // note: `i` and `j` must be GROUP LEADERS
    void unite(int i, int j) {
        if (i == j) return;
        if (r[i] > r[j]) swap(i, j);
        if (r[i] == r[j]) r[j] += 1;
        p[i] = j;
    }
};

struct Seg {
    int c, l, r;
};

int N;
vector<Seg> segs;
Dsu dsu;
set<pair<int, int>> active[2];
set<int> distinct;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        segs.resize(N);
        rep(i, N) {
            int c, l, r;
            cin >> c >> l >> r;
            segs[i] = {c, l, r};
        }

        dsu.reset(N);
        sort(segs.begin(), segs.end(),
             [](Seg& l, Seg& r) { return l.l < r.l; });
        rep(c, 2) active[c].clear();

        rep(i, N) {
            Seg& s = segs[i];
            rep(c, 2) while (!active[c].empty() &&
                             active[c].begin()->first < s.l) {
                // cerr << "removing interval active till "
                //     << active[c].begin()->first << endl;
                active[c].erase(active[c].begin());
            }

            // cerr << "at t = " << s.l << endl;
            active[s.c].insert({s.r, i});
            // cerr << "added c" << s.c << " segment [" << s.l << ", " << s.r
            //     << "]" << endl;
            if (!active[!s.c].empty()) {
                // join all active segments
                // cerr << "joining " << active[0].size() << " + "
                //     << active[1].size() << " segments" << endl;
                int gl[2];
                rep(c, 2) {
                    // cerr << "  joining c" << c << " segments" << endl;
                    int gr = 0, lj = -1;
                    for (auto [r, j] : active[c]) {
                        // cerr << "    joining segment [" << segs[j].l << ", "
                        //     << segs[j].r << "]" << endl;
                        gr = max(gr, r);
                        if (lj != -1) {
                            dsu.unite(lj, dsu.find(j));
                        } else {
                            lj = j;
                        }
                        lj = dsu.find(lj);
                    }
                    active[c].clear();
                    active[c].insert({gr, lj});
                    gl[c] = lj;
                }
                dsu.unite(gl[0], gl[1]);
            }
        }

        distinct.clear();
        rep(i, N) distinct.insert(dsu.find(i));
        // cerr << "ans = " << distinct.size() << endl;
        cout << distinct.size() << "\n";
    }
}
