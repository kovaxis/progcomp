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

pair<int, int> a[100005];

bool check() {
    int n, k;
    cin >> n >> k;
    rep(i, n) {
        int x;
        cin >> x;
        a[i] = {x, i};
    }
    sort(a, a + n);
    int nextidx = -1;
    int req = 0;
    rep(i, n) {
        if (a[i].second != nextidx) req += 1;
        nextidx = a[i].second + 1;
    }
    return k >= req;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        if (check()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
