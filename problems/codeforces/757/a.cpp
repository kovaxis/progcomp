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
    rep(t, T) {
        int N, L, R, K;
        cin >> N >> L >> R >> K;
        vector<int> schoko;
        rep(i, N) {
            int x;
            cin >> x;
            if (L <= x && x <= R) schoko.push_back(x);
        }
        sort(schoko.begin(), schoko.end());
        ll amount = 0, total = 0;
        for (int x : schoko) {
            total += x;
            if (total > K) break;
            amount += 1;
        }
        cout << amount << "\n";
    }
}
