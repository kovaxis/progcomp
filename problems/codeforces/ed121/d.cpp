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

int N, ans;
vector<int> counts;

inline int ceil_log2(int n) { return n <= 1 ? 0 : 32 - __builtin_clz(n - 1); }

int cnt(int i, int j) { return counts[j] - counts[i - 1]; }

void searchpow(int stage, int i, int supercost) {
    if (stage >= 2) {
        int n = cnt(i, N);
        int cost = (1 << ceil_log2(n)) - n;
        ans = min(ans, supercost + cost);
        // cerr << "stage 2 at range [" << i << ", " << N << "] costs " << cost
        //     << ", " << supercost + cost << " total" << endl;
        return;
    }
    int nextpow = 1, j = i - 1;
    while (true) {
        while (j + 1 <= N && cnt(i, j + 1) <= nextpow) j += 1;
        int cost = nextpow - cnt(i, j);
        // cerr << "stage " << stage << " at range [" << i << ", " << j
        //     << "] costs " << cost << endl;
        searchpow(stage + 1, j + 1, supercost + cost);
        if (nextpow >= N) break;
        nextpow <<= 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        counts.assign(N + 2, 0);
        rep(i, N) {
            int x;
            cin >> x;
            counts[x]++;
        }
        rep(i, 1, N + 2) counts[i] += counts[i - 1];

        ans = INT32_MAX;
        searchpow(0, 1, 0);
        cout << ans << "\n";
    }
}
