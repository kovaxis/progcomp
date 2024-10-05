// https://codeforces.com/contest/1556/problem/F

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll &x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

const int MOD = 1e9 + 7;

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

int N;
vector<int> A;

int P[14][14];
int MP[14][1 << 14];
umap<int, int> MMP;
int DP[14][1 << 14];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];

    rep(u, N) rep(v, N) {
        P[u][v] = (ll)A[u] * multinv((A[u] + A[v]) % MOD, MOD) % MOD;
        cerr << "prob(" << A[u] << ", " << A[v] << ") = " << P[u][v] << endl;
    }

    rep(u, N) {
        MP[u][0] = 1;
        repx(m, 1, 1 << N) {
            int v = __builtin_ctz(m);
            int sm = m & ~(1 << v);
            MP[u][m] = (ll)MP[u][sm] * P[u][v] % MOD;
            cerr << "mprob[" << u << "][" << m << "] = " << MP[u][m] << endl;
        }
    }

    rep(m, 1 << N) for (int sm = m; true; sm = (sm - 1) & m) {
        int a = sm;
        int b = m & ~a;
        ll x = 1;
        rep(u, N) if (a & (1 << u)) x = x * MP[u][b] % MOD;
        MMP[(a << 14) | b] = x;
        cerr << "mmprob[" << a << ", " << b << "] = " << x << endl;
        if (!sm) break;
    }

    rep(m, 1 << N) rep(u, N) if (m & (1 << u)) {
        if (m == 1 << u) {
            DP[u][m] = 1;
        } else {
            int v = __builtin_ctz(m & ~(1 << u));
            cerr << "DP[" << u << "][" << m << "]: u = " << u << ", v = " << v << endl;
            int mm = m & ~(1 << u) & ~(1 << v);
            for (int sm = mm; true; sm = (sm - 1) & mm) {
                int a = sm | (1 << u);
                int b = m & ~a;
                int b_not_v = b & ~(1 << v);
                cerr << "  parts: " << DP[u][a] << " " << DP[v][b] << " " << (MOD + 1 - MP[v][a]) % MOD << " " << MMP[(b_not_v << 14) | a] << endl;
                ll sub = (ll)DP[u][a] * DP[v][b] % MOD * (MOD + 1 - MP[v][a]) % MOD * MMP[(b_not_v << 14) | a] % MOD;
                cerr << "  a = " << a << ", b = " << b << ": " << sub << endl;
                DP[u][m] = (DP[u][m] + sub) % MOD;
                if (!sm) break;
            }
            cerr << "DP[" << u << "][" << m << "] = " << DP[u][m] << endl;
        }
    }

    int ans = 0;
    rep(u, N) ans = (ans + DP[u][(1 << N) - 1]) % MOD;
    cout << ans << endl;
}
