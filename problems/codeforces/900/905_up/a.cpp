#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
vector<int> A, B;

ll solve() {
    A[0] = 2e9;
    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());
    int i = 0;
    int d = 0;
    rep(j, N) {
        while (i < N && A[i] >= B[j]) i += 1;
        if (i == N) {
            d = N - j;
            break;
        }
        i += 1;
    }

    int bottle = 0, bottle_v = -1;
    rep(j, N) {
        if (j + d - 1 < N && A[j + d - 1] >= B[j]) {
            bottle += 1;
            bottle_v = B[j];
        }
    }

    ll y = min(M, bottle_v - 1);

    return (ll)d * (M - y) + ll(d - 1) * y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        A.resize(N);
        repx(i, 1, N) {
            cin >> A[i];
        }
        B.resize(N);
        rep(i, N) cin >> B[i];
        cout << solve() << "\n";
    }
}
