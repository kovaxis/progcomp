
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

ll N;
bool found_ans;
ll ans_i;
ll ans_k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    ll i = 0;
    ll f1 = 1, f2 = 0;
    while (true) {
        ll x = f1 + f2;
        f2 = f1, f1 = x;
        if (x > N) break;
        ll k = 0;
        while (true) {
            ll y = x << k;
            if (y > N) break;
            if (y == N) {
                found_ans = true;
                ans_i = i;
                ans_k = k;
            }
            k += 1;
        }
        i += 1;
    }

    if (!found_ans) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    rep(i, ans_i) cout << "A";
    cout << "B";
    rep(i, ans_k) cout << "AB";
    cout << "\n";
}