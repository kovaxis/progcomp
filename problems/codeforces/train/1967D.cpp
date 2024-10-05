// https://codeforces.com/contest/1967/problem/D

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

int N, M, T;
vector<int> A, B;
vector<int> L, R, D, root;
vector<bool> seen, seen2;
vector<vector<int>> G;

void dfs(int u, int c) {
    seen[u] = true;
    root[u] = c;
    L[u] = T++;
    for (int v : G[u]) {
        if (seen[v]) {
            assert(v == c);
        } else {
            D[v] = D[u] + 1;
            dfs(v, c);
        }
    }
    R[u] = T++;
}

bool is_in_subtree(int up, int dn) {
    return L[dn] >= L[up] && R[dn] <= R[up];
}

int dist(int u, int v) {
    int d = 1e9;
    if (is_in_subtree(v, u)) {
        d = min(d, D[u] - D[v]);
    }
    if (is_in_subtree(v, B[root[u]])) {
        d = min(d, D[u] + 1 + D[B[root[u]]] - D[v]);
    }
    return d;
}

bool cansolve(int K) {
    cerr << "checking solvability with " << K << endl;

    int i = 0, j = 0;
    while (i < N && j < M) {
        if (dist(A[i], j) <= K) {
            cerr << "  making " << A[i] << " into " << j << endl;
            i += 1;
        } else {
            j += 1;
        }
    }
    cerr << "  solvable: " << (i == N) << endl;
    return i == N;
}

int solve() {
    cerr << "solving with N = " << N << " and M = " << M << endl;
    cerr << "A:";
    rep(i, N) cerr << " " << A[i];
    cerr << endl;
    cerr << "B:";
    rep(j, M) cerr << "   " << j << "->" << B[j];
    cerr << endl;

    G.assign(M, {});
    rep(u, M) G[B[u]].push_back(u);

    T = 0;
    L.assign(M, -1), R.assign(M, -1), D.assign(M, 0);
    root.assign(M, -1), seen.assign(M, false), seen2.assign(M, false);
    rep(u, M) if (!seen[u]) {
        int v = u;
        while (!seen2[v]) {
            seen2[v] = true;
            v = B[v];
        }
        dfs(v, v);
    }

    int l = 0, r = M + 1;
    while (l != r) {
        int m = (l + r) / 2;
        if (cansolve(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cerr << "can solve with " << l << " tricks" << endl;
    if (l == M + 1) return -1;
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        A.resize(N), B.resize(M);
        rep(i, N) cin >> A[i];
        rep(i, N) A[i] -= 1;
        rep(j, M) cin >> B[j];
        rep(j, M) B[j] -= 1;
        cout << solve() << "\n";
    }
}
