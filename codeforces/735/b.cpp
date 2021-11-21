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

int a[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        ll n, k;
        cin >> n >> k;
        rep(i, n) cin >> a[i];
        ll maxidx[2] = {n - 1, n};
        ll maxval[2] = {a[n - 2], a[n - 1]};
        ll maxmul = n * (n - 1) - k * (maxval[0] | maxval[1]);
        invrep(i, 1, n - 1) {
            ll mul0 = maxidx[0] * i - k * (maxval[0] | a[i - 1]);
            ll mul1 = i * maxidx[1] - k * (a[i - 1] | maxval[1]);
            if (mul0 > mul1) {
                if (mul0 > maxmul) {
                    maxidx[1] = (ll)i;
                    maxval[1] = a[i - 1];
                    maxmul = mul0;
                }
            } else {
                if (mul1 > maxmul) {
                    maxidx[0] = (ll)i;
                    maxval[0] = a[i - 1];
                    maxmul = mul1;
                }
            }
        }
        cout << maxmul << '\n';
    }
}
