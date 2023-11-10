#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> A;

bool solve() {
    rep(k, 10) {
        int K = 1 << k;
        repx(i, min(K / 2, N), min(K, N) - 1) {
            if (A[i] > A[i + 1]) return false;
        }
    }
    return true;
}

int main()

{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];

        cout << (solve() ? "YES" : "NO") << "\n";
    }
}
