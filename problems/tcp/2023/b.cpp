#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> A, P, S, T, to;

int find(int u) {
    if (P[u] != u) P[u] = find(P[u]);
    return P[u];
}

void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (S[u] > S[v]) swap(u, v);
    P[u] = v, S[v] += S[u], T[v] = max(T[u], T[v]);
}

int f(int x) {
    if (x == 0) return 0;
    return 1 + f(x / 2);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];
    rep(i, N) A[i]--;

    P.resize(N + 1), S.resize(N + 1), T.resize(N + 1);
    rep(i, N + 1) P[i] = i, T[i] = i, S[i] = 1;

    to.resize(N);
    invrep(i, N) {
        to[A[i]] = T[find(A[i] + 1)];
        unite(A[i], A[i] + 1);
    }

    vector<bool> close(N + 1);
    rep(i, N) close[to[i]] = true;
    bool open = false;
    int cuts = 0;
    rep(i, N) {
        if (close[i]) cuts += open, open = false;
        if (to[i] != N) open = true;
    }

    cout << f(cuts) << endl;
}
