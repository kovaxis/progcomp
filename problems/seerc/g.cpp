#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

int N;
vector<ll> X, R, A;
vector<ll> ans;

void try_r1(ll r1) {
    if (!ans.empty()) return;

    map<ll, int> cnt;
    rep(i, N) cnt[R[i]] += 1;

    vector<ll> sol;
    rep(i, N) {
        ll r;
        if (i % 2) {
            // odd: A[i] - r1
            r = A[i] - r1;
        } else {
            // even: A[i] + r1
            r = A[i] + r1;
        }
        if (cnt[r] == 0) return;
        cnt[r] -= 1;
        sol.push_back(r);
    }
    ans = sol;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    X.resize(N), R.resize(N);
    rep(i, N) cin >> X[i];
    rep(i, N) cin >> R[i];

    // radius of even gears: A[i] + r1
    // radius of odd gears:  A[i] - r1
    A.resize(N);
    repx(i, 1, N) {
        A[i] = (X[i] - X[i - 1]) - A[i - 1];
    }

    ll min_r = INT64_MAX;
    rep(i, N) min_r = min(min_r, R[i]);

    ll min_even = INT64_MAX, min_odd = INT64_MAX;
    rep(i, N) if (i % 2) min_odd = min(min_odd, A[i]);
    else min_even = min(min_even, A[i]);

    try_r1(min_r - min_even);
    try_r1(min_odd - min_r);

    assert(!ans.empty());
    rep(i, N) cout << ans[i] << " \n"[i == N - 1];
}