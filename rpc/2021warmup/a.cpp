#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int n;
int ring[400001];
ll ringacc[800001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    ll acc = 0;
    rep(i, n) {
        int x;
        cin >> x;
        acc += x;
        ring[i] = x;
        ringacc[i] = acc;
    }
    ll s = acc;
    if (s % 2 == 1) {
        cout << "N\n";
        return 0;
    }
    int pairs = 0;
    rep(i, n) {
        int findval = ringacc[i] + s / 2;
        int idx =
            lower_bound(ringacc + i, ringacc + i + n, findval) - ringacc - i;
        if (idx < n && ringacc[i + idx] == findval) {
            pairs += 1;
        }
        acc += ring[i];
        ringacc[i + n] = acc;
    }
    if (pairs >= 4) {
        cout << "Y\n";
    } else {
        cout << "N\n";
    }
}
