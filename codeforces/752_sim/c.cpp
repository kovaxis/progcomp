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

template <class T>
struct Map {
    int N;
    vector<bool> used;
    vector<int> keys;
    vector<T> vals;

    Map() {}
    // O(C)
    void resize(int C) {
        C += 1, used.resize(C), keys.resize(C), vals.resize(C);
    }

    // O(1)
    T& operator[](int k) {
        if (!used[k]) used[k] = true, keys[N++] = k, vals[k] = T();
        return vals[k];
    }

    // O(N)
    void clear() {
        while (N) used[keys[--N]] = false;
    }

    // O(N)
    template <class OP>
    void iterate(OP op) {
        rep(i, N) op(keys[i], vals[keys[i]]);
    }
};

const int INF = 1e9;
const ll MOD = 998244353;

int N, M;
vector<int> a;
// b-value -> {segments, acc}
Map<pair<int, ll>> bset, bset2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        M = 0;
        rep(i, N) M = max(M, a[i]);
        bset.resize(M + 1), bset2.resize(M + 1);

        ll ans = 0;
        bset.clear();
        invrep(i, N) {
            bset2.clear();
            bset[M + 1] = {1, 0};
            bset.iterate([&](int b, pair<int, ll>& v1) {
                int cnt = v1.first;
                ll acc = v1.second;
                int f = (a[i] + b - 1) / b;
                b = a[i] / f;
                acc = (acc + (ll)cnt * (f - 1) % MOD) % MOD;
                auto& v2 = bset2[b];
                v2.first += cnt;
                v2.second = (v2.second + acc) % MOD;

                ans = (ans + acc) % MOD;
            });
            swap(bset, bset2);
        }
        cout << ans << "\n";
    }
}
