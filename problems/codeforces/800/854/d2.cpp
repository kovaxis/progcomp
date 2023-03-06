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

template <class T>
struct Stl3 {
    // immediate, lazy
    vector<pair<T, T>> a;

    T qneutral() { return 0; }
    T merge(T l, T r) { return l + r; }
    T uneutral() { return 0; }
    void update(pair<T, T> &u, T val, int l, int r) { u.first += val * (r - l), u.second += val; }

    Stl3() {}
    Stl3(int N) : a(4 * N, {qneutral(), uneutral()}) {} // node neutral

    void push(int v, int vl, int vm, int vr) {
        update(a[2 * v], a[v].second, vl, vm);     // node update
        update(a[2 * v + 1], a[v].second, vm, vr); // node update
        a[v].second = uneutral();                  // update neutral
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v].first; // query op
        if (l >= vr || r <= vl) return qneutral(); // query neutral
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) update(a[v], val, vl, vr); // node update
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, val, 2 * v, vl, vm);
            update(l, r, val, 2 * v + 1, vm, vr);
            a[v].first = merge(a[2 * v].first, a[2 * v + 1].first); // node merge
        }
    }
};

int N, K;
vector<int> a;
vector<ll> hot, cold;

Stl3<ll> dp;
ll dpmin;

const ll INF = 1e17;

ll getdp(int i) {
    return dp.query(i, i + 1);
}

void setdp(int i, ll v) {
    dp.update(i, i + 1, v - getdp(i));
    dpmin = min(dpmin, v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        a.resize(N);
        cold.resize(K), hot.resize(K);
        rep(i, N) cin >> a[i];
        rep(i, N) a[i] -= 1;
        rep(k, K) cin >> cold[k];
        rep(k, K) cin >> hot[k];

        dp = {K};
        dp.update(0, K, INF);
        dpmin = INF;
        setdp(a[0], cold[a[0]]);

        repx(n, 1, N) {
            ll special = min(getdp(a[n]) + hot[a[n]], dpmin + cold[a[n]]);

            ll add = a[n - 1] == a[n] ? hot[a[n]] : cold[a[n]];
            dp.update(0, K, add);
            dpmin += add;

            setdp(a[n], special);
            setdp(a[n - 1], special);
        }

        // dp[n][k] = minimum time of running programs [0, n], and finishing with programs a[n] and k in the cache
        // dp[n][K] = minimum time of running programs [0, n], and finishing with a[n] and any other in the cache
        /*
        dp.assign(N, vector<ll>(K + 1, INF));
        dp[0][a[0]] = cold[a[0]];
        dp[0][K] = dp[0][a[0]];
        repx(n, 1, N) {
            rep(k, K) {
                if (k == a[n] || k == a[n - 1]) {
                    dp[n][k] = min(dp[n - 1][a[n]] + hot[a[n]], dp[n - 1][K] + cold[a[n]]);
                } else {
                    dp[n][k] = dp[n - 1][k] + (a[n - 1] == a[n] ? hot[a[n]] : cold[a[n]]);
                }
                cerr << "dp[" << n + 1 << "][" << k + 1 << "] = " << dp[n][k] << endl;
                dp[n][K] = min(dp[n][K], dp[n][k]);
            }
            cerr << "dp[" << n + 1 << "][?] = " << dp[n][K] << endl;
        }*/

        cout << dpmin << "\n";
    }
}
