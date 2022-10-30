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
vector<vector<int>> G;
vector<bool> part, part2;
vector<int> perm;
int counts[2];

void split(int i, int p = 0) {
    part[i] = !part[p];
    for (int c : G[i])
        if (c != p) split(c, i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        part.resize(N + 1), perm.resize(N + 1);
        G.assign(N + 1, vector<int>());
        rep(i, N - 1) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        split(1);
        rep(k, 2) counts[k] = 0;
        rep(i, N) counts[part[i + 1]] += 1;

        int k = counts[1] < counts[0];
        part2.assign(N + 1, !k);
        rep(i, 31) if ((1 << i) & counts[k]) rep(j, 1 << i)
            part2[(1 << i) | j] = k;
        int ptr[2];
        ptr[0] = 1, ptr[1] = 1;
        rep(i, 1, N + 1) {
            int k = part[i];
            while (part2[ptr[k]] != k) ptr[k] += 1;
            perm[i] = ptr[k]++;
        }
        rep(i, N) cout << perm[i + 1] << " \n"[i == N - 1];
    }
}
