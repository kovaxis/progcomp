#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

// const int M = int(2e5) + 5;
// const int M = 12;

int N;
ll B, X;
vector<int> C;
vector<ll> D, E;

ll force(ll c, ll k) {
    ll kh = c % k;
    ll kl = k - kh;
    ll l = c / k;
    ll h = (c + k - 1) / k;
    return kl * (kl - 1) / 2 * l * l + kh * (kh - 1) / 2 * h * h + l * h * kl * kh;
}

ll solve() {
    int M = 0;
    rep(i, N) M = max(M, C[i]);
    M += 4;

    D.assign(M, 0);
    E.assign(M, 0);
    rep(i, N) {
        repx(k, 1, C[i] + 1) {
            cerr << "force of race " << i + 1 << " with " << k << " squads: " << force(C[i], k) << endl;
            D[k] += force(C[i], k);
            if (k == C[i]) {
                E[k + 1] += force(C[i], k);
            }
        }
    }
    rep(m, M) {
        if (m > 0) E[m] += E[m - 1];
        D[m] += E[m];
        cerr << "total force with " << m << " squads: " << D[m] << endl;
    }

    ll mx = 0;
    repx(k, 1, M) {
        ll score = D[k] * B - (k - 1) * X;
        mx = max(mx, score);
    }
    return mx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> B >> X;
        C.resize(N);
        rep(i, N) cin >> C[i];
        cout << solve() << "\n";
    }
}
