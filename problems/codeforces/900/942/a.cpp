#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
ll K;
vector<ll> A;

bool canfill(ll lvl) {
    ll k = K;
    rep(i, N) if (A[i] < lvl) {
        k -= (lvl - A[i]);
        if (k < 0) return false;
    }
    return true;
}

ll maxfill() {
    ll l = 0, r = 1e18;
    while (r - l > 1) {
        ll m = (l + r) / 2;
        if (canfill(m)) l = m;
        else r = m;
    }
    return l;
}

ll solve() {
    ll f = maxfill();
    rep(i, N) if (A[i] < f) {
        K -= (f - A[i]);
        A[i] = f;
    }
    assert(K >= 0);
    rep(i, N) if (A[i] == f && K > 0) A[i] += 1, K -= 1;

    sort(A.begin(), A.end());

    int gt = 0;
    rep(i, N) gt += (A[i] > A[0]);

    return 1 + (A[0] - 1) * N + gt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        A.resize(N);
        rep(i, N) cin >> A[i];
        cout << solve() << "\n";
    }
}
