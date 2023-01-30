#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll N, M;
vector<ll> a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    a.resize(N);
    rep(i, N) cin >> a[i];

    multiset<ll> b;
    rep(i, N) b.insert(a[i]);

    vector<ll> ans;

    auto last = --b.end();
    ll lx = *last;
    ans.push_back(lx);
    b.erase(last);
    while (!b.empty()) {
        ll largest_allowed = M - lx;
        auto end = b.upper_bound(largest_allowed);

        if (end == b.begin()) end = b.end();
        end = --end;
        lx = *end;
        ans.push_back(lx);
        b.erase(end);
    }

    ll toll = 1;
    rep(i, N - 1) {
        if (ans[i + 1] + ans[i] > M) toll += 1;
    }

    rep(i, N) toll += ans[i];

    cout << toll << endl;
}
