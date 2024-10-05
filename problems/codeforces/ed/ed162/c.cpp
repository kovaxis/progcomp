#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, Q;
vector<ll> A, ones, sm;
vector<int> L, R;

bool solve(int l, int r) {
    if (r - l == 1) return false;
    return sm[r] - sm[l] >= ones[r] - ones[l];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> Q;
        A.resize(N);
        rep(i, N) cin >> A[i];
        L.resize(Q), R.resize(Q);
        rep(q, Q) {
            cin >> L[q] >> R[q];
            L[q] -= 1;
        }

        ones.assign(N + 1, 0);
        rep(i, N) ones[i + 1] = ones[i] + (A[i] == 1);
        sm.assign(N + 1, 0);
        rep(i, N) sm[i + 1] = sm[i] + (A[i] - 1);

        rep(q, Q) cout << (solve(L[q], R[q]) ? "YES" : "NO") << "\n";
    }
}
