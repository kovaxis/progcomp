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

ll N, Q;
vector<ll> a;
ll ans;

int findl(int i) {
    if (i == 0) return false;
    return a[i] == a[i - 1];
}
int findr(int i) {
    if (i + 1 >= N) return false;
    return a[i + 1] == a[i];
}

void setx(int i, ll x) {
    int l = findl(i);
    int r = findr(i);
    cerr << "  old l = " << l << ", r = " << r << endl;
    if (l) ans += i * (N - i);
    if (r) ans += (N - i - 1) * (i + 1);

    a[i] = x;

    l = findl(i);
    r = findr(i);
    cerr << "  new l = " << l << ", r = " << r << endl;
    if (l) ans -= i * (N - i);
    if (r) ans -= (N - i - 1) * (i + 1);

    cerr << "after setting a[" << i << "] = " << x << " ans is " << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    a.assign(N, 0);
    ans = N * (N + 1) / 2;
    cerr << "initial ans is " << ans << endl;
    rep(i, N) {
        ll x;
        cin >> x;
        setx(i, x);
    }
    rep(q, Q) {
        ll i, x;
        cin >> i >> x;
        setx(i - 1, x);
        cout << ans << "\n";
    }
}
