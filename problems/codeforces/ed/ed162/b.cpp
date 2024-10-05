#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
vector<ll> A, X, H;
ll ammo;
int nxt;

bool shoot(int at) {
    ll cnt = min(ammo, H[at]);
    ammo -= cnt;
    H[at] -= cnt;
    return H[at] == 0;
}

bool solve() {
    H.assign(N + 10, 0);
    rep(i, N) H[abs(X[i])] += A[i];

    int x = 0;
    nxt = 0;
    while (x <= N) {
        ammo = K;
        while (nxt <= N && shoot(nxt)) nxt += 1;
        x += 1;
        if (H[x] > 0) return false;
    }
    return true;
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
        X.resize(N);
        rep(i, N) cin >> X[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    }
}
