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
int a[200001];

int signum(int x) {
    if (x < 0)
        return -1;
    else if (x > 0)
        return 1;
    else
        return 0;
}
bool isgood(int i, int j, int k) {
    return signum(a[k] - a[j]) * signum(a[j] - a[i]) < 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> n;
        rep(i, n) cin >> a[i];
        ll good = 0;
        rep(i, n) {
            good += 1;
            if (i + 1 < n) good += 1;
            if (i + 2 < n) good += isgood(i, i + 1, i + 2);
            if (i + 3 < n)
                good += isgood(i, i + 1, i + 2) && isgood(i, i + 1, i + 3) &&
                        isgood(i, i + 2, i + 3) && isgood(i + 1, i + 2, i + 3);
        }
        cout << good << '\n';
    }
}
