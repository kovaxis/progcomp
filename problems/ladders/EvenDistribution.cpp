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

int I, S;
vector<set<int>> G;
vector<int> candies;

vector<set<int>> processed;
bitset<100001> possible;

void process(int i, int k) {
    k = __gcd(k, candies[i]);
    if (processed[i].count(k)) return;
    possible.set(k);
    processed[i].insert(k);
    for (int c : G[i]) process(c, k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> I) {
        cin >> S;
        G.assign(I, set<int>()), candies.resize(I),
            possible = {}, processed.assign(I, set<int>());
        rep(i, I) cin >> candies[i];
        rep(s, S) {
            int u, v;
            cin >> u >> v;
            G[u - 1].insert(v - 1);
            G[v - 1].insert(u - 1);
        }

        rep(i, I) process(i, 0);

        cout << possible.count() << "\n";
    }
}
