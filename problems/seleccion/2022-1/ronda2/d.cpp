#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;
    deque<pair<ll, ll>> que;
    rep(q, Q) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            // push_back
            ll x, n;
            cin >> x >> n;
            que.push_back({x, n});
        } else if (ty == 2) {
            // pop_front
            ll n, ans = 0;
            cin >> n;
            while (n > 0) {
                auto& [qx, qn] = que.front();
                if (n < qn) {
                    ans += qx * n;
                    qn -= n;
                    n = 0;
                } else {
                    ans += qx * qn;
                    n -= qn;
                    que.pop_front();
                }
            }
            cout << ans << "\n";
        }
    }
}
