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

bool vowel[128];

ll mincost(string& s, char into) {
    ll cost = 0;
    for (char c : s) {
        if (c == into) continue;
        cost += 1 + (vowel[c] == vowel[into]);
    }
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vowel['A'] = true;
    vowel['E'] = true;
    vowel['I'] = true;
    vowel['O'] = true;
    vowel['U'] = true;

    int T;
    string s;
    cin >> T;
    rep(t, T) {
        cin >> s;
        ll cost = INT64_MAX;
        rep(i, 26) cost = min(cost, mincost(s, 'A' + i));
        cout << "Case #" << t + 1 << ": " << cost << "\n";
    }
}
