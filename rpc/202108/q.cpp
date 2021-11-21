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

ll fun(ll n) { return n * (3 * n - 1) / 2; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        ll n;
        cin >> n;
        ll begin = 1, end = 1e7;
        while (end > begin) {
            ll mid = begin + (end - begin) / 2;
            // cerr << "mid = " << mid << ", fun(mid) = " << fun(mid) << endl;
            if (n < fun(mid)) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        }
        // cerr << "found " << begin << endl;
        ll n1 = begin - 1, n2 = begin;
        if (abs(n - fun(n1)) <= abs(n - fun(n2))) {
            cout << fun(n1) << '\n';
        } else {
            cout << fun(n2) << '\n';
        }
    }
}
