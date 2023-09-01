#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
vector<int> A;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        A.resize(N + 1);
        rep(i, N) cin >> A[i];

        vector<bool> seen(N + 1, false);
        rep(i, N) seen[A[i]] = true;
        rep(i, N + 1) if (!seen[i]) A[N] = i;

        K %= N + 1;
        if (K != 0)
            rotate(A.begin(), A.end() - K, A.end());

        rep(i, N) cout << A[i] << " \n"[i == N - 1];
    }
}
