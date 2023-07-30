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
map<int, map<int, int>> B[2];

int reflect(int l, int i) {
    return l + K - (i - l) - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    A.resize(N);
    rep(i, N) cin >> A[i];

    rep(i, N) {
        B[i % 2][A[i]][i] = 0;
    }

    rep(k, 2) for (auto &p : B[k]) {
        int i = 0;
        for (auto &q : p.second) q.second = i++;
        p.second[INT_MAX] = i;
    }

    ll ans = 0;
    rep(i, N) {
        int l = max(0, i - K / 2);
        int r = min(i, N - K);
        int n = r - l + 1;
        if (n <= 0) continue;

        int a = reflect(l, i);
        int b = reflect(r, i);
        int cnt = B[i % 2][A[i]].upper_bound(b)->second - B[i % 2][A[i]].lower_bound(a)->second;
        // cerr << cnt << " number " << A[i] << "s between indices [" << a + 1 << ", " << b + 1 << "], and total is " << n << ": +" << n - cnt << endl;
        ans += n - cnt;
    }
    cout << ans << endl;

    // rep(j, K / 2) {
    //     rep(i, N - K + 1) {
    //         ans += (A[i + j] != A[i + K - j - 1]);
    //     }
    // }
    // cout << ans << endl;
}
