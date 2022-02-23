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
string s;
vector<int> ct[3];

bool works(int i, int j) {
    int a = ct[0][j + 1] - ct[0][i];
    int b = ct[1][j + 1] - ct[1][i];
    int c = ct[2][j + 1] - ct[2][i];
    return a > b && a > c;
}

int solve() {
    cin >> N >> s;
    rep(k, 3) ct[k].assign(N + 1, 0);
    rep(i, N) ct[s[i] - 'a'][i + 1] = 1;
    rep(k, 3) rep(i, N) ct[k][i + 1] += ct[k][i];

    int i[3];
    int mn = 1e9;

    i[0] = 0, i[1] = 0;
    rep(j, N) {
        if (s[j] != 'a') continue;
        i[1] = i[0];
        i[0] = j;
        if (i[0] - i[1] + 1 < 2) continue;
        if (works(i[1], i[0])) mn = min(mn, i[0] - i[1] + 1);
    }

    i[0] = 0, i[1] = 0, i[2] = 0;
    rep(j, N) {
        if (s[j] != 'a') continue;
        i[2] = i[1];
        i[1] = i[0];
        i[0] = j;
        if (i[0] - i[2] + 1 < 2) continue;
        if (works(i[2], i[0])) mn = min(mn, i[0] - i[2] + 1);
    }

    if (mn == 1e9) mn = -1;
    return mn;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) { cout << solve() << '\n'; }
}
