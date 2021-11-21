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

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    int lin = n, aux2 = m, splits = 0;
    while (aux > 0 and aux2 > 1) {
        splits++;
        lin = lin / 2;
        aux2--;
    }
    cout << lin + splits;
    int maxx = lin << splits;

    int bot = 0;
    if (splits > 0) {
        bot = lin;
        rep(i, splits - 1) {}
    }
}
