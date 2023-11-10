#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<ll> A;

ll solve() {
    sort(A.begin(), A.end());
    int i = 0, j = N - 1;
    ll x = 0, ans = 0;
    while (i < j) {
        if (x == A[j]) {
            ans += 1;
            x = 0;
            j--;
        } else {
            ll k = min(A[i], A[j] - x);
            ans += k;
            x += k;
            A[i] -= k;
            if (A[i] == 0) i++;
        }
    }
    assert(i == j);

    ll k = (A[j] - x) / 2;
    ans += k;
    x += k;
    A[j] -= k;

    if (x > 0) A[j] -= x, ans += 1;

    ans += A[j];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];
        cout << solve() << "\n";
    }
}
