#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
string S;
int E, M, A;

bool solve(int x) {
    if (x < M) return false;
    x -= M;
    x -= min(x / 2, E) * 2;
    if (x >= 2) return false;
    if (x == 1 && A) return true;
    return x == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> S;
        N = S.size();

        E = 0, M = 0;
        rep(i, N / 2)(S[i] == S[N - i - 1] ? E : M) += 1;
        A = N % 2;

        string ans(N + 1, ' ');
        rep(x, N + 1) ans[x] = '0' + solve(x);
        cout << ans << "\n";
    }
}
