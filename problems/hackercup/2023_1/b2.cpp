#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// gets the prime factorization of a number in O(sqrt(n))
vector<pair<ll, int>> factorize(ll x) {
    vector<pair<ll, int>> f;
    for (ll k = 2; x > 1; k++) {
        if (k * k > x) {
            f.push_back({x, 1});
            break;
        }
        int n = 0;
        while (x % k == 0) x /= k, n++;
        if (n > 0) f.push_back({k, n});
    }
    return f;
}

ll sum(vector<ll> &A) {
    ll s = 0;
    for (ll x : A) s += x;
    return s;
}

vector<ll> A, C;
vector<bool> B;
vector<ll> ans;
ll ans_cost;

void backtrack() {
    if (sum(C) > 41) return;
    bool end = true;
    rep(i, A.size()) if (B[i]) {
        end = false;
        ll old = C.back();
        C.back() *= A[i];
        B[i] = false;
        backtrack();
        B[i] = true;
        C.back() = old;
    }
    if (end) {
        ll cost = C.size() + (41 - sum(C));
        if (cost < ans_cost) {
            ans = C;
            ans_cost = cost;
        }
        return;
    }
    rep(i, A.size()) if (B[i]) {
        C.push_back(A[i]);
        B[i] = false;
        backtrack();
        B[i] = true;
        C.pop_back();
        break;
    }
}

void solve() {

    ll P;
    cin >> P;
    vector<pair<ll, int>> f = factorize(P);

    A.clear();
    for (auto [x, n] : f) {
        rep(i, n) A.push_back(x);
    }

    if (sum(A) > 41) {
        cout << "-1\n";
        return;
    }

    ans.clear();
    ans_cost = 1e18;
    B.assign(A.size(), true);
    C.clear();
    C.push_back(A[0]);
    B[0] = false;
    backtrack();

    while (sum(ans) < 41) ans.push_back(1);

    cout << ans.size();
    for (ll x : ans) cout << " " << x;
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cout << "Case #" << tc + 1 << ": ";
        solve();
    }
}
