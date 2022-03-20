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

int N, K;
vector<int> a, b, bsum;
int lastx;

// count amount of numbers in the range [l, r]
// 0 <= l, r < N
int countbetween(int l, int r) { return bsum[r + 1] - bsum[l]; }

bool works(int yminusx) {
    rep(x, N) {
        int y = x + yminusx;
        if (y >= N) break;

        int inside = countbetween(x, y);
        int outside = countbetween(0, N - 1) - inside;
        if (inside - outside >= K) {
            lastx = x;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> K;
        a.resize(N);
        rep(i, N) cin >> a[i];
        rep(i, N) a[i] -= 1;

        b.assign(N, 0);
        rep(i, N) b[a[i]] += 1;

        bsum.resize(N + 1);
        rep(i, N) bsum[i + 1] = bsum[i] + b[i];

        // cerr << "checking testcase" << endl;

        int l = 0, r = N;
        while (l != r) {
            int m = (l + r) / 2;
            if (works(m)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        // cerr << "got y - x = " << l << endl;

        assert(works(l));
        int x = lastx, y = lastx + l;
        // cerr << "got x = " << x << ", y = " << y << endl;
        cout << x + 1 << " " << y + 1 << "\n";
        int diff = 0;  // inside - outside
        int last = 0;
        rep(i, N) {
            bool inside = x <= a[i] && a[i] <= y;
            diff += (inside ? 1 : -1);
            if (diff >= 1) {
                K -= 1;
                if (K == 0) {
                    cout << last + 1 << " " << N << "\n";
                    break;
                }
                cout << last + 1 << " " << i + 1 << "\n";
                last = i + 1;
                diff = 0;
            }
        }
        // cerr << endl;
    }
}
