#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

double ans;

void check_out(double d) {
    ans = max(ans, d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        int N;
        cin >> N;
        vector<double> A(N);
        rep(i, N) cin >> A[i];

        sort(A.begin(), A.end());
        ans = 0;

        if (N == 5) {
            check_out((A[3] + A[4]) / 2 - (A[0] + A[2]) / 2);
            check_out((A[2] + A[4]) / 2 - (A[0] + A[1]) / 2);
        } else {
            double a = (A[0] + A[1]) / 2;
            double b = (A[N - 2] + A[N - 1]) / 2;
            ans = (b - a);
        }

        cout << "Case #" << fixed << setprecision(8) << (tc + 1) << ": " << ans << "\n";
    }
}
