#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

struct R {
    ll n, d;

    R(ll n, ll d) : n(n), d(d) {
        assert(n >= 0 && d > 0);
        ll g = __gcd(n, d);
        n /= g, d /= g;
    }

    friend ostream &operator<<(ostream &s, R r) {
        return s << r.n << "/" << r.d;
    }

    friend istream &operator>>(istream &s, R &r) {
        s >> r.n >> r.d;
        r = R(r.n, r.d);
        return s;
    }

    bool operator<(R r) const {
        // n / d < r.n / r.d
        return (__int128_t)n * r.d < (__int128_t)r.n * d;
    }

    bool operator<=(R r) const {
        return !(r < *this);
    }

    bool operator==(R r) const {
        return *this <= r && r <= *this;
    }

    R operator+(R r) const {
        ll g = __gcd(d, r.d);
        return R(r.d / g * n + d / g * r.n, d / g * r.d);
    }
};

int N;
ll X;
vector<ll> C;
vector<vector<int>> G;
vector<int> P;
vector<ll> M, T, I, ADD;

R deriv(int i, ll x) {
    return R(T[i] - M[i], (T[i] + x) * (M[i] + x));
}

R discrete_improve(int i, ll x) {
    return R((T[i] + x) * (M[i] + x + 1), (M[i] + x) * (T[i] + x + 1));
}

void setp(int u, int p) {
    P[u] = p;
    for (int v : G[u])
        if (v != p) setp(v, u);
}

void dfs(int u, int p) {
    ll m = 0, t = 0, i = -1;
    for (int v : G[u])
        if (v != p) {
            if (v == P[u]) {
                // good
                m += C[v];
                dfs(v, u);
                i = v;
            }
            t += C[v];
        }
    if (i != -1) {
        cerr << "i = " << I.size() << ", M = " << m << ", T = " << t << ", I = " << i + 1 << endl;
        M.push_back(m);
        T.push_back(t);
        I.push_back(i);
    }
}

bool enough_cheese(R A) {
    cerr << "reducing derivs to " << A << endl;

    vector<ll> add(I.size());
    rep(i, I.size()) {
        ll l = 0, r = X;
        while (l != r) {
            ll m = (l + r) / 2;
            if (deriv(i, m) <= A) r = m;
            else l = m + 1;
        }
        cerr << "  adding " << l << " cheese to " << I[i] + 1 << ", moving deriv from " << deriv(i, 0) << " to " << deriv(i, l) << endl;
        add[i] = l;
    }

    ll rem = X;
    rep(i, I.size()) rem -= add[i];
    if (rem < 0) return false;

    ADD = add;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> X;
    C.resize(N);
    rep(i, N) cin >> C[i];
    G.resize(N);
    rep(j, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    P.resize(N);
    setp(N - 1, N - 1);

    dfs(0, 0);

    // approximate
    R l = R(0, 1), r = R(1, 1);
    ADD.resize(I.size());
    while (true) {
        R m = l + r;
        m.d <<= 1;
        if (m.d < 0) break;
        if (enough_cheese(m)) r = m;
        else l = m;
    }

    // add remaining cheese
    ll rem = X;
    rep(i, I.size()) rem -= ADD[i];
    priority_queue<pair<R, int>> q;
    rep(i, I.size()) q.push({discrete_improve(i, ADD[i]), i});
    while (rem > 0) {
        int i = q.top().second;
        q.pop();

        rem -= 1;
        ADD[i] += 1;
        q.push({discrete_improve(i, ADD[i]), i});
    }

    // reconstruct answer
    vector<ll> ans(N);
    rep(i, I.size()) ans[I[i]] = ADD[i];

    rep(i, N) cout << ans[i] << " \n"[i == N - 1];
}
