#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

void factorize(vector<pair<ll, int>>& facts, ll x) {
    ll k = 2;
    while (x > 1) {
        if (k * k > x) {
            facts.push_back({x, 1});
            break;
        }
        int n = 0;
        while (x % k == 0) x /= k, n++;
        if (n > 0) facts.push_back({k, n});
        k += 1;
    }
}

template <class OP>
void divisors(ll x, OP op) {
    vector<pair<ll, int>> facts;
    factorize(facts, x);
    vector<int> f(facts.size());
    while (true) {
        ll y = 1;
        rep(i, f.size()) rep(j, f[i]) y *= facts[i].first;
        op(y);

        int i = 0;
        while (i < f.size()) {
            f[i] += 1;
            if (f[i] > facts[i].second)
                f[i++] = 0;
            else
                break;
        }
        if (i == f.size()) break;
    }
}

set<ll> ans;

void find_tiling(ll n) {
    divisors(n, [](ll x) { ans.insert(x); });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        ll W, H;
        cin >> W >> H;

        ans.clear();
        rep(k1, 2) rep(k2, 2) rep(k3, 2) rep(k4, 2) {
            ll up = W - 2, dn = W - 2;
            ll lt = H - 2, rt = H - 2;
            (k1 ? lt : up) += 1;
            (k2 ? up : rt) += 1;
            (k3 ? rt : dn) += 1;
            (k4 ? dn : lt) += 1;
            ll n = __gcd(__gcd(lt, rt), __gcd(up, dn));
            find_tiling(n);
        }
        cout << ans.size();
        for (ll x : ans) cout << " " << x;
        cout << "\n";
    }
}