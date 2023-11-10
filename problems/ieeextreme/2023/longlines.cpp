#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll N, H, A, C, Q;
vector<ll> B;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> H >> A >> C >> Q;
    B.resize(N);
    rep(i, N) {
        B[i] = H;
        H = (A * H + C) % Q;
    }

    vector<int> stk;
    ll ans = 0;
    rep(i, N) {
        while (stk.size() && B[stk.back()] <= B[i]) {
            ans += i - stk.back();
            stk.pop_back();
        }
        stk.push_back(i);
    }
    for (int i : stk) {
        ans += N - 1 - i;
    }

    cout << ans << endl;
}
