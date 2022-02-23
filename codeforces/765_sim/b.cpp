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

int N, A;
vector<int> a;
vector<vector<int>> b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];
        A = 0;
        rep(i, N) A = max(A, a[i] + 1);
        b.assign(A, {});
        rep(i, N) b[a[i]].push_back(i);
        int len = 1e9;
        rep(i, A) rep(j, 1, b[i].size()) len = min(len, b[i][j] - b[i][j - 1]);
        cout << (len == 1e9 ? -1 : N - len) << "\n";
    }
}
