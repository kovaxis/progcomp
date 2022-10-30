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

int adj[20001 * 50][10];
int counts[20001 * 50];
int M = 1;
ll total = 0;

ll visit(int i) {
    ll t = 0;
    rep(j, 10) {
        if (adj[i][j] == 0) continue;
        t += counts[adj[i][j]] + visit(adj[i][j]);
    }
    // cerr << "node " << i << " has " << t << " active children" << endl;
    total += counts[i] * t;
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    string s;
    cin >> N;
    rep(i, N) {
        cin >> s;
        int cur = 0;
        rep(j, s.size()) {
            int& pt = adj[cur][s[j] - '0'];
            cur = pt;
            if (cur == 0) cur = pt = M++;
            if (j == s.size() - 1) counts[cur] += 1;
        }
    }
    visit(0);
    cout << total << endl;
}
