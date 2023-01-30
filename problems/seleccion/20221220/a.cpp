#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll N, A[2], d;
vector<pair<ll, ll>> ans;

int large() {
    return A[0] > A[1] ? 0 : 1;
}

void add(ll a, ll b) {
    ans.push_back({a, b});
    d += (a == b);
    N -= 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> A[0] >> A[1];

    if (N == 1) {
        add(A[0], A[1]);
    } else {
        while (N >= 3 || (A[!large()] == 0 && N >= 2)) {
            ll m[2];
            rep(k, 2) m[k] = 0;
            if (A[large()] > 0) {
                m[large()] = 1;
                A[large()] -= 1;
            }
            add(m[0], m[1]);
        }
        while (N > 0) {
            ll m[2];
            rep(k, 2) m[k] = 0;
            m[large()] = A[large()];
            A[large()] = 0;
            add(m[0], m[1]);
        }
    }

    cout << d << "\n";
    for (auto [a, b] : ans) cout << a << ":" << b << "\n";
}
