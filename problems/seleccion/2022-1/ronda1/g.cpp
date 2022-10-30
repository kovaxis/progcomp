#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<ll> a;
map<int, ll> bmn, bmx;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) cin >> a[i];

    ll ans = 0, s = 0;
    rep(r, N) {
        int x = a[r];

        bmn[x] += 1;
        while (true) {
            auto it = --bmn.end();
            int y = it->first;
            ll cnt = it->second;
            if (y <= x) break;
            bmn[x] += cnt;
            s += cnt * (y - x);
            bmn.erase(it);
        }

        bmx[x] += 1;
        while (true) {
            auto it = bmx.begin();
            int y = it->first;
            ll cnt = it->second;
            if (y >= x) break;
            bmx[x] += cnt;
            s += cnt * (x - y);
            bmx.erase(it);
        }

        ans += s;
    }

    cout << ans << endl;
}
