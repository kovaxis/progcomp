#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
ll M;
vector<ll> A;
pair<ll, ll> ans;
ll last = -1;
int nxt_le, nxt_ge;

ll score(ll x) {
    while (nxt_le < N && A[nxt_le] <= x) nxt_le += 1;
    ll l_score = nxt_le - K < 0 ? x + 1 : x - (A[nxt_le - K] + x) / 2;

    while (nxt_ge < N && A[nxt_ge] < x) nxt_ge += 1;
    ll r_score = nxt_ge + K - 1 >= N ? M - x + 1 : (A[nxt_ge + K - 1] + x + 1) / 2 - x;

    // cerr << "score for " << x << " is " << l_score << " " << r_score << endl;

    ll s = max(0ll, l_score + r_score - 1);
    return s;
}

void tryout(ll x) {
    if (x <= last || x > M) return;
    last = x;
    ll y = score(x);
    if (y > ans.first || (y == ans.first && x < ans.second)) ans = {y, x};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    A.resize(N);
    rep(i, N) cin >> A[i];

    sort(A.begin(), A.end());

    ans = {-1, 0};
    tryout(0);
    for (ll xc : A) {
        // if (xc % 1000 == 0) cerr << "trying " << xc << endl;
        tryout(xc - 2);
        tryout(xc - 1);
        tryout(xc);
        tryout(xc + 1);
        tryout(xc + 2);
    }
    tryout(M);

    cout << ans.first << " " << ans.second << endl;
}
