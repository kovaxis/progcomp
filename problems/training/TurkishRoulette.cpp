#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int n, m;
int rawslots[251];
int slotvals[251];
int slot(int idx) { return slotvals[idx % n]; }
int ballvals[130];

// ball, from, to
// max_win
int dp_store[130][251][251];
int zero = 0;
int impossible = -0x7fffffff;
int& dp(int b, int from, int to) {
    if (b >= m) return zero;
    if (to <= from) return impossible;
    return dp_store[b][from % n][to % n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        cin >> n >> m;
        if (n == 0 || m == 0) break;
        rep(i, n) { cin >> rawslots[i]; }
        rep(i, n) { slotvals[i] = -(rawslots[i] + rawslots[(i + 1) % n]); }

        rep(i, m) { cin >> ballvals[i]; }
        invrep(b, m) {
            int bval = ballvals[b];
            rep(to, n, 2 * n) {
                int maxwin = impossible;
                invrep(from, to - n, to) {
                    int nextwin = dp(b + 1, from + 2, to);
                    if (nextwin != impossible) {
                        maxwin = max(maxwin, bval * slot(from) + nextwin);
                    }
                    dp(b, from, to) = maxwin;
                }
            }
        }
        int maxwin = impossible;
        rep(i, n) { maxwin = max(maxwin, dp(0, i, i + n - 1)); }
        cout << maxwin << '\n';
    }
}
