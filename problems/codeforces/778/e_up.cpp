#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll N, A, S;
vector<ll> a;
map<ll, ll> score;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) cin >> a[i];
    A = 1;
    rep(i, N) A = max(A, a[i] + 1);
    S = sqrt(A) + 1;

    ll ans = 0;
    repx(d, -S, S + 1) {
        score.clear();
        // real = memory + off
        // memory = real - off
        ll off = 0;
        rep(i, N) {
            off += d;
            score[a[i] - off] += 1;
        }
        for (auto p : score) ans = max(ans, p.second);
    }

    cerr << "up to sqrt = " << ans << endl;

    rep(i, N) {
        score.clear();
        repx(j, i + 1, min(i + S, N)) {
            if ((a[j] - a[i]) % (j - i) != 0) continue;
            ll d = (a[j] - a[i]) / (j - i);
            score[d] += 1;
        }
        for (auto p : score) ans = max(ans, p.second + 1);
    }
    cerr << "over sqrt = " << ans << endl;

    cout << N - ans << endl;
}
