#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k;
    ll d, s;
    cin >> n >> k >> d >> s;
    ll sumrest = d * n - s * k;
    if (sumrest > (n - k) * 100 || sumrest < 0) {
        cout << "impossible\n";
    } else {
        double avgrest = ((double)sumrest) / ((double)(n - k));
        cout << fixed << setprecision(7) << avgrest << endl;
    }
}
