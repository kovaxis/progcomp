#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class T>
struct St {
    int n;
    vector<T> a;

    T neut() { return 1e9; }
    T merge(T x, T y) { return min(x, y); }

    St(int n = 0) : n(n), a(2 * n, neut()) {}

    T query(int l, int r) {
        T x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, T x) {
        for (a[i += n] = x; i /= 2;) a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};

int N, M;
vector<pair<int, int>> A;
St<int> L, R;
vector<int> dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    A.resize(M);
    rep(j, M) {
        cin >> A[j].first >> A[j].second;
    }

    L = {N + 1};
    R = {N + 1};
    rep(j, M) {
        auto [l, r] = A[j];
        R.update(l, min(R.query(l, l + 1), r));
        L.update(r, min(L.query(r, r + 1), l));
    }

    dp.resize(N + 1, -1e9);
    dp[0] = 0;
    repx(i, 1, N + 1) {
        if (R.query(i, i + 1) == int(1e9)) {
            // try not placing a beer
            dp[i] = max(dp[i], dp[i - 1]);
        }
        int j = min(i, L.query(i, N + 1));
        if (R.query(j, i) >= i) {
            // try placing a beer
            dp[i] = max(dp[i], dp[j - 1] + 1);
        }
    }

    if (dp[N] <= int(-1e8)) {
        cout << "-1" << endl;
    } else {
        cout << dp[N] << endl;
    }
}
