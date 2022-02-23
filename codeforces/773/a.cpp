#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    map<ll, ll> a;
    vector<ll> b;
    ll N, X;
    while (T--) {
        cin >> N >> X;
        a.clear();
        b.resize(N);
        rep(i, N) {
            ll y;
            cin >> y;
            a[y] += 1;
            b[i] = y;
        }
        sort(b.begin(), b.end());

        int add = 0;
        for (ll y : b) {
            if (!a[y]) continue;
            if (a[y * X]) {
                a[y * X] -= 1;
            } else {
                add += 1;
            }
            a[y] -= 1;
        }
        cout << add << "\n";
    }
}
