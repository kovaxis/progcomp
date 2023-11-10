#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, Q;
vector<int> A;
vector<vector<int>> B;
vector<int> X;

void solve() {
    B.assign(31, {});
    rep(i, N) {
        B[__builtin_ctz(A[i])].push_back(i);
    }
    rep(q, Q) {
        repx(x, X[q], 31) {
            for (int i : B[x]) {
                A[i] += 1 << (X[q] - 1);
                B[X[q] - 1].push_back(i);
            }
            B[x].clear();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> Q;
        A.resize(N);
        X.resize(Q);
        rep(i, N) cin >> A[i];
        rep(q, Q) cin >> X[q];
        solve();
        rep(i, N) cout << A[i] << " ";
        cout << "\n";
    }
}
