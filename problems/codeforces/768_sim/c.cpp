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
// idx -> value
vector<int> a;
// value -> first idx with value
vector<int> first;
// idx -> last idx with the same value
// (or -1 if no such thing)
vector<int> match;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) cin >> a[i];
    rep(i, N) a[i] -= 1;

    first.assign(N, -1);
    match.assign(N, -1);
    rep(i, N) {
        if (first[a[i]] == -1) first[a[i]] = i;
        match[first[a[i]]] = i;
    }
    rep(i, N) if (match[i] == i) match[i] = -1;

    // cerr << "match:";
    // rep(i, N) cerr << " " << match[i];
    // cerr << endl;

    int i = 0;
    int ans = 0;
    while (i < N) {
        if (match[i] == -1) {
            i += 1;
            continue;
        }
        // open range
        // cerr << "checking range [" << i << ", " << match[i] << "]" << endl;
        int maxclose = -1;
        rep(j, i + 1, match[i]) {
            maxclose = max(maxclose, match[j]);
            ans += 1;
        }
        if (maxclose <= match[i]) maxclose = -1;
        i = match[i];
        match[i] = maxclose;
    }
    cout << ans << "\n";
}
