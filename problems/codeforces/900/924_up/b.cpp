#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;
        vector<ll> A(N);
        rep(i, N) cin >> A[i];
        set<ll> B;
        rep(i, N) B.insert(A[i]);
        A.clear();
        for (ll x : B) A.push_back(x);

        int n = A.size();
        int j = 0, ans = 0;
        rep(i, n) {
            while (j < n && A[j] - A[i] <= N - 1) j += 1;
            // cerr << "for " << i + 1 << ": " << j << endl;
            ans = max(ans, j - i);
        }
        cout << ans << "\n";
    }
}
