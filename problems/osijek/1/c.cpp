#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

const int M = 1 << 20;
const int MOD = 998244353;

int N, ans;
vector<int> A;
vector<int> Ak[21];
vector<int> DPk[21];

int add(int a, int b) {
    a += b;
    return a < MOD ? a : a - MOD;
}

int sub(int a, int b) {
    a -= b;
    return a < 0 ? a + MOD : a;
}

void fht(vector<int> &a, bool inv) {
    for (int l = 1; 2 * l <= M; l *= 2)
        for (int i = 0; i < M; i += 2 * l) rep(j, l) {
                int u = a[i + j], v = a[i + l + j];
                if (!inv) a[i + j] = add(u, v), a[i + l + j] = u;
                else a[i + j] = v, a[i + l + j] = sub(u, v);
            }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];

    rep(k, 21) Ak[k].resize(M);
    rep(i, N) Ak[__builtin_popcount(A[i])][A[i]] += 1;
    rep(k, 21) fht(Ak[k], false);

    DPk[0].resize(M);
    DPk[0][0] = 1;
    fht(DPk[0], false);

    repx(k, 1, 21) {
        DPk[k].resize(M);
        rep(k2, k) {
            rep(m, M) DPk[k][m] = (DPk[k][m] + (ll)DPk[k2][m] * Ak[k - k2][m]) % MOD;
        }
        fht(DPk[k], true);
        rep(m, M) if (__builtin_popcount(m) != k) DPk[k][m] = 0;
        rep(m, M) ans = add(ans, DPk[k][m]);
        fht(DPk[k], false);
    }

    cout << ans << endl;
}
