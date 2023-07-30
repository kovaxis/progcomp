#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

int N;
vector<int> A, B;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N), B.resize(N);
        rep(i, N) cin >> A[i];
        rep(i, N) cin >> B[i];

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        ll ans = 1;
        int j = 0;
        rep(i, N) {
            while (j < N && B[j] < A[i]) j++;
            ans = ans * (j - i) % MOD;
        }

        cout << ans << "\n";
    }
}
