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

int a[200001];
pair<long long, int> negs[200001];
int drinkable[200001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    rep(i, n) { cin >> a[i]; }
    ll mod = 0;
    int count = 0;
    int negc = 0;
    invrep(i, n) {
        if (a[i] >= 0) {
            mod -= a[i];
            count += 1;
        } else {
            negs[negc] = {-a[i], a[i] + mod};
            negc += 1;
        }
    }
    sort(negs, negs + negc);
    rep(i, negc) {
        if (-negs[i].second + mod <= 0) {
            mod += negs[i].first;
            count += 1;
        }
    }
    cout << count << endl;
}
