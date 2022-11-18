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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<int> dists(N * M);
        rep(y, N) rep(x, M) {
            // rahul sits here
            int dist = 0;
            dist = max(dist, abs(0 - x) + abs(0 - y));
            dist = max(dist, abs(M - 1 - x) + abs(0 - y));
            dist = max(dist, abs(0 - x) + abs(N - 1 - y));
            dist = max(dist, abs(M - 1 - x) + abs(N - 1 - y));
            dists[y * M + x] = dist;
        }
        sort(dists.begin(), dists.end());
        rep(i, N * M) cout << dists[i] << " \n"[i == N * M - 1];
    }
}
