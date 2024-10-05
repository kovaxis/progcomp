#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, X, Y;
vector<int> A, gap;
vector<bool> used;

int solve() {
    sort(A.begin(), A.end());

    gap.clear();
    int ans = X - 2;
    rep(i, X) {
        int g = (A[(i + 1) % X] - A[i] + N) % N - 1;
        if (g <= 1) {
            ans += (g == 1);
        } else {
            gap.push_back(g);
        }
    }

    used.assign(gap.size(), false);
    sort(gap.begin(), gap.end());

    rep(i, gap.size()) {
        int g = gap[i];
        if (g % 2 == 1 && Y >= g / 2) {
            ans += g;
            Y -= g / 2;
            used[i] = true;
        }
    }

    rep(i, gap.size()) if (!used[i]) {
        int g = gap[i];
        int y = min(Y, g / 2);
        Y -= y;
        ans += 2 * y;
        used[i] = true;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> X >> Y;
        A.resize(X);
        rep(i, X) cin >> A[i];
        rep(i, X) A[i] -= 1;
        cout << solve() << "\n";
    }
}
