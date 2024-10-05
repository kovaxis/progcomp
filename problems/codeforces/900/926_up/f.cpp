#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int MOD = 998244353;

ll binexp(ll a, ll e, ll M) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a % M;
        a = a * a % M;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

int N, M;
vector<int> L, R, V;
vector<int> A;

void dfs(int u) {
    if (L[u] >= 0) dfs(L[u]);
    A.push_back(V[u]);
    if (R[u] >= 0) dfs(R[u]);
}

int choose(int n, int k) {
    if (k < 0 || k > n) return 0;
    ll res = 1;
    repx(x, n - k + 1, n + 1) {
        res = res * x % MOD;
    }
    ll den = 1;
    repx(x, 1, k + 1) den = den * x % MOD;
    return res * multinv(den, MOD) % MOD;
}

int multichoose(int n, int k) {
    return choose(n + k - 1, k);
}

int seq(int l, int r, int n) {
    return multichoose(r - l + 1, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        L.resize(N), R.resize(N), V.resize(N);
        rep(u, N) {
            cin >> L[u] >> R[u] >> V[u];
            L[u] -= 1;
            R[u] -= 1;
        }

        A.clear();
        A.push_back(1);
        dfs(0);
        A.push_back(M);

        int ans = 1;
        int last = 0;
        rep(i, (int)A.size()) {
            if (A[i] != -1) {
                int n = i - last - 1;
                if (n > 0) {
                    ans = (ll)ans * seq(A[last], A[i], n) % MOD;
                }
                last = i;
            }
        }

        cout << ans << "\n";
    }
}
