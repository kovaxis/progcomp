#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

bool solve() {
    int N, K;
    cin >> N >> K;
    vector<int> B(N);
    rep(i, N) cin >> B[i];

    vector<bool> seen(N);
    int a = 0;
    rep(k, K) {
        if (seen[a]) return true;
        seen[a] = true;

        int x = (a - 1 + N) % N;
        if (B[x] > N) return false;
        a = ((x - B[x] + 1) % N + N) % N;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cout << (solve() ? "Yes" : "No") << "\n";
    }
}
