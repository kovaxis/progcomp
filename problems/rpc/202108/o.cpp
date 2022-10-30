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

int N;
pair<ll, string> dogs[1001];
string win[3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, N) cin >> dogs[i].second >> dogs[i].first;
    sort(dogs, dogs + N);
    int W = min(N, 3);
    ll sheep = 1;
    rep(i, W) {
        win[i] = dogs[N - i - 1].second;
        sheep *= dogs[N - i - 1].first;
    }
    sort(win, win + W);
    rep(i, W) cout << win[i] << " ";
    cout << sheep << "\n";
}
