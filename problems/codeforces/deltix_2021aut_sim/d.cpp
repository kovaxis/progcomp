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

struct Dsu {
    vector<int> p, r;

    Dsu() {}
    // initialize the disjoint-set-union to all unitary sets
    void resize(int N) {
        p.resize(N), r.assign(N, 0);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two disjoint sets with leaders `i` and `j`
    // note: `i` and `j` must be LEADERS OF TWO SEPARATE SETS
    int unite(int i, int j) {
        if (r[i] > r[j]) {
            p[j] = i;
            return j;
        } else {
            if (r[i] == r[j]) r[j] += 1;
            p[i] = j;
            return i;
        }
    }
};

int N, Q;
Dsu groups;
vector<int> counts;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    groups.resize(N);
    int extra = 0;
    rep(q, Q) {
        int x, y;
        cin >> x >> y;
        x = groups.find(x - 1), y = groups.find(y - 1);
        if (x == y)
            extra += 1;
        else
            groups.unite(x, y);

        counts.assign(N, 0);
        rep(i, N) groups.find(i);
        rep(i, N) counts[groups.find(i)] += 1;
        sort(counts.begin(), counts.end());
        int ans = 0;
        invrep(i, max(0, N - extra - 1), N) ans += counts[i];

        cout << ans - 1 << "\n";
    }
}
