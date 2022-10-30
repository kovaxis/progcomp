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

    // perform union on the two sets that `i` and `j` belong to
    void unite(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        if (r[i] > r[j]) swap(i, j);
        if (r[i] == r[j]) r[j] += 1;
        p[i] = j;
    }
};

int N, M, K;
vector<pair<int, int>> plan;
Dsu dsu;

bool all_the_same(int up_to) {
    dsu.reset(N);
    rep(t, up_to) {
        dsu.unite(plan[t].first, plan[t].second);
    }
    int i = 0;
    while (i < N) {
        int color = -1;
        rep(j, K) {
            if (i >= N) break;
            if (color == -1) color = dsu.find(i);
            if (color != dsu.find(i)) return false;
            i += 1;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> N >> M >> K;
        plan.resize(M);
        rep(t, M) {
            int u, v;
            cin >> u >> v;
            plan[t].first = u - 1;
            plan[t].second = v - 1;
        }

        int l = 0, r = M + 1;
        while (l != r) {
            int m = (l + r) / 2;
            if (all_the_same(m)) {
                r = m;
            } else {
                l = m + 1;
            }
        }

        int ans = l;
        if (ans > M) ans = -1;

        cout << "Case #" << tc + 1 << ": " << ans
             << "\n";
    }
}
