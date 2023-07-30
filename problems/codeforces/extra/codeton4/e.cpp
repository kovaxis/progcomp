#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

struct Dsu {
    vector<int> p, s;

    // initialize the disjoint-set-union to all unitary sets
    void reset(int N) {
        p.resize(N), s.assign(N, 1);
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
        if (s[i] > s[j]) swap(i, j);
        s[j] += s[i];
        p[i] = j;
    }
};

int N, M;
vector<int> A;
vector<bool> Z;
vector<vector<int>> G;
Dsu dsu;

struct Reach {
    int from, to;

    bool operator<(Reach r) const {
        return A[to] > A[r.to];
    }
};

vector<priority_queue<Reach>> B;

bool solve() {
    dsu.reset(N);
    B.resize(N);
    rep(i, N) {
        while (!B[i].empty()) B[i].pop();
    }

    Z.assign(N, 0);
    rep(i, N) if (A[i] == 0) Z[i] = true;

    rep(i, N) for (int v : G[i]) B[i].push({i, v});

    rep(i, N) {
        if (dsu.find(i) != i) continue;
        auto q = &B[i];
        while (!q->empty()) {
            Reach r = q->top();
            int ul = dsu.find(r.from);
            int vl = dsu.find(r.to);
            if (!Z[ul] || A[r.to] > dsu.s[ul]) break;
            q->pop();

            if (ul != vl) {
                cerr << "eating " << r.to + 1 << " from " << r.from + 1 << endl;
                cerr << "  previous size was " << dsu.s[ul] << endl;
                dsu.unite(r.from, r.to);
                int uvl = dsu.find(r.from);
                int froml = uvl == ul ? vl : ul;
                if (B[uvl].size() < B[froml].size())
                    swap(B[uvl], B[froml]);
                while (!B[froml].empty()) {
                    B[uvl].push(B[froml].top());
                    B[froml].pop();
                }
                q = &B[uvl];
                Z[uvl] = Z[ul] || Z[vl];
                cerr << "  new size is " << dsu.s[uvl] << endl;
            }
        }
    }

    return dsu.s[dsu.find(0)] == N;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        A.resize(N);
        rep(i, N) cin >> A[i];
        G.assign(N, {});
        rep(j, M) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        cout << (solve() ? "YES" : "NO") << "\n";
    }
}
