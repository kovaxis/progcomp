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

void prefunc(const string& s, vector<int>& p) {
    int N = s.size(), j;
    p.resize(N), p[0] = 0;
    rep(i, 1, N) {
        for (j = p[i - 1]; j > 0 && s[j] != s[i];) j = p[j - 1];
        p[i] = j + (s[j] == s[i]);
    }
}

int N;
string s;
vector<int> pi, cd;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;
    N = s.size();
    prefunc(s, pi);

    cd.resize(N);
    for (int i = pi[N - 1]; i > 0; i = pi[i - 1]) cd[i] |= 1;
    rep(i, 1, N - 1) cd[pi[i]] |= 2;

    int ans = 0;
    rep(i, N) if (cd[i] == 3) ans = max(ans, i);

    if (ans == 0)
        cout << "Just a legend\n";
    else
        cout << s.substr(0, ans);
}
