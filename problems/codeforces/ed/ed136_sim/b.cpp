//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<ll> a, d;

bool solve() {
    a.resize(N + 1);
    rep(i, N) {
        // a[i+1] = a[i] +/- d
        ll an = a[i] - d[i];
        ll ap = a[i] + d[i];
        if (an < 0) an = ap;
        if (an != ap) return false;
        a[i + 1] = ap;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        d.resize(N);
        rep(i, N) cin >> d[i];

        if (!solve()) cout << "-1\n";
        else rep(i, N) cout << a[i + 1] << " \n"[i == N - 1];
    }
}
