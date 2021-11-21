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
int boxes[200001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    rep(i, n) {
        int x;
        cin >> x;
        boxes[x] += 1;
    }
    ll carry = 0;
    int setbits = 0;
    rep(i, 200001) {
        carry += boxes[i];
        boxes[i] = carry & 1;
        carry >>= 1;
        setbits += boxes[i];
    }
    if (setbits == 2 || (setbits == 1 && n >= 2)) {
        cout << "Y\n";
    } else {
        cout << "N\n";
    }
}
