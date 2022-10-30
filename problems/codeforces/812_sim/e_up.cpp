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
    void unite(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        if (r[i] > r[j]) swap(i, j);
        if (r[i] == r[j]) r[j] += 1;
        p[i] = j;
    }
};

int N;
vector<vector<int>> a, b;
vector<int> as;
Dsu dsu;

int assig(int i) {
    i = dsu.find(i);
    if (as[i] != -1) return as[i];
    int j = dsu.find((i + N) % (2 * N));
    if (as[j] != -1) return as[i] = !as[j];
    return as[i] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.assign(N, vector<int>(N));
        rep(i, N) rep(j, N) cin >> a[i][j];
        dsu.reset(2 * N);
        rep(i, N) rep(j, N) if (j > i) {
            int x, ax, y, ay;
            if (a[i][j] < a[j][i]) {
                x = i, ax = i + N, y = j, ay = j + N;
            } else if (a[i][j] > a[j][i]) {
                x = i, ax = i + N, y = j + N, ay = j;
            } else {
                continue;
            }
            if (dsu.find(x) == dsu.find(ay) || dsu.find(y) == dsu.find(ax))
                continue;
            dsu.unite(x, y), dsu.unite(ax, ay);
        }
        as.assign(2 * N, -1);
        rep(i, N) if (assig(i)) rep(j, N) swap(a[i][j], a[j][i]);
        rep(i, N) rep(j, N) cout << a[i][j] << " \n"[j == N - 1];

        if (false) {
            cerr << "groupings:";
            rep(i, 2 * N) cerr << " " << dsu.find(i);
            cerr << endl;

            cerr << "flip: |";
            rep(i, N) cerr << " X"[assig(i)];
            cerr << "|" << endl;
        }
    }
}
