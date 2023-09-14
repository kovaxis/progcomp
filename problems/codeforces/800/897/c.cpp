#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
set<int> A;

void solve() {
    int mex;
    rep(i, N + 1) if (A.count(i) == 0) {
        mex = i;
        break;
    }

    while (mex >= 0) {
        cout << mex << endl;
        cin >> mex;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.clear();
        rep(i, N) {
            int x;
            cin >> x;
            A.insert(x);
        }
        solve();
    }
}
