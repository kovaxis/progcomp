#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int M;
vector<int> N;
vector<vector<ll>> A, C;
vector<ll> L, R;

ll solve() {
    cin >> M;
    N.resize(M), A.resize(M), C.resize(M), L.resize(M), R.resize(M);
    rep(i, M) {
        cin >> N[i] >> L[i] >> R[i];
        A[i].resize(N[i]), C[i].resize(N[i]);
        rep(j, N[i]) cin >> A[i][j];
        rep(j, N[i]) cin >> C[i][j];
    }

    ll Lg = 0, Rg = 0;
    rep(i, M) Lg += L[i], Rg += R[i];

    map<ll, ll> mn, mx;
    rep(i, M) {
        ll sm = 0;
        rep(j, N[i]) sm += C[i][j];
        rep(j, N[i]) {
            mn[A[i][j]] += max(0ll, L[i] - (sm - C[i][j]));
            mx[A[i][j]] += max(0ll, R[i] - (sm - C[i][j]));
        }
    }

    ll min_score = Rg;
    for (ll cnt = Lg; cnt <= Rg; cnt++) {
        // minimize the number of cnt
        ll score = mn[cnt];
        ll bad = mx[cnt] - mn[cnt];
        ll good = Rg - Lg - bad;

        ll need_to_add = cnt - Lg;

        ll add = min(need_to_add, good);
        good -= add;
        need_to_add -= add;

        add = min(need_to_add, bad);
        bad -= add;
        need_to_add -= add;
        score += add;

        min_score = min(min_score, score);
        if (min_score == 0) return 0;
    }

    return min_score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cout << solve() << "\n";
    }
}
