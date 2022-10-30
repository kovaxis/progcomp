#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    a.resize(M);
    rep(i, M) cin >> a[i];
    sort(a.begin(), a.end());

    bool ok = true;
    rep(i, M - 2) {
        if (a[i] == a[i + 1] - 1 && a[i] == a[i + 2] - 2) ok = false;
    }
    if (M > 0) {
        if (a[0] == 1 || a[M - 1] == N) ok = false;
    }

    cout << (ok ? "YES" : "NO") << endl;
}
