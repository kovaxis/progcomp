#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

struct Sparse {
    int op(int a, int b) { return min(a, b); }

    vector<vector<int>> st;
    Sparse() {}
    Sparse(vector<int> a) : st{a} {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        repx(i, 1, npot) rep(j, N + 1 - (1 << i))
            st[i]
                .push_back(
                    op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));
    }

    int query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return op(st[i][l], st[i][r - (1 << i)]);
    }
};

vector<int> suffixarray(const string &s) {
    int N = s.size() + 1;
    vector<int> p(N), p2(N), c(N), c2(N), cnt(256);
    rep(i, N) cnt[s[i]] += 1;
    repx(b, 1, 256) cnt[b] += cnt[b - 1];
    rep(i, N) p[--cnt[s[i]]] = i;
    repx(i, 1, N) c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);

    for (int k = 1; k < N; k <<= 1) {
        int C = c[p[N - 1]] + 1;
        cnt.assign(C + 1, 0);
        for (int &pi : p) pi = (pi - k + N) % N;
        for (int cl : c) cnt[cl + 1] += 1;
        rep(i, C) cnt[i + 1] += cnt[i];
        rep(i, N) p2[cnt[c[p[i]]]++] = p[i];
        c2[p2[0]] = 0;
        repx(i, 1, N) c2[p2[i]] = c2[p2[i - 1]] + (c[p2[i]] != c[p2[i - 1]] || c[(p2[i] + k) % N] != c[(p2[i - 1] + k) % N]);
        swap(c, c2), swap(p, p2);
    }
    p.erase(p.begin());
    return p;
}

vector<int> makelcp(const string &s, const vector<int> &p) {
    int N = p.size(), k = 0;
    vector<int> r(N), lcp(N);
    rep(i, N) r[p[i]] = i;
    rep(i, N) {
        if (r[i] + 1 >= N) {
            k = 0;
            continue;
        }
        int j = p[r[i] + 1];
        while (i + k < N && j + k < N && s[i + k] == s[j + k]) k += 1;
        lcp[r[i]] = k;
        if (k) k -= 1;
    }
    return lcp;
}

struct Edge {
    int v;
    int l, r, n;
};

const ll INF = 1e18;

int N, M, An, start;
string A;
vector<vector<Edge>> G, Ginv;
vector<int> ord2pos, pos2ord;
Sparse lcp;

vector<bool> DPexist, canreach;
vector<vector<Edge>> DP;

int lcp_cmp(int i, int j, int K) {
    if (i == j) return 0;
    int ii = pos2ord[i], jj = pos2ord[j];
    int l = lcp.query(min(ii, jj), max(ii, jj));
    if (l >= K) return 0;
    return ii < jj ? -1 : 1;
}

void dp(int v) {
    if (DPexist[v]) return;
    DPexist[v] = true;

    if (v == start) {
        canreach[v] = true;
        return;
    }

    vector<vector<Edge>> paths;
    vector<int> parents;
    for (Edge e : Ginv[v]) {
        int u = e.v;
        e.v = v;
        dp(u);
        if (canreach[u]) {
            vector<Edge> path = DP[u];
            path.push_back(e);
            paths.push_back(path);
            parents.push_back(u);
        }
    }

    if (paths.empty()) {
        canreach[v] = false;
        return;
    } else {
        canreach[v] = true;
    }

    int K = paths.size();
    vector<int> ptr(K), active(K, true);
    vector<ll> len(K);
    cerr << "DP(" << v + 1 << ") with " << K << " paths:" << endl;
    rep(k, K) {
        cerr << "  from node " << parents[k] + 1 << ":";
        for (Edge e : paths[k]) cerr << " (-> " << e.v + 1 << ", [" << e.l + 1 << ", " << e.r << "])";
        cerr << endl;
    }
    ll L = 0;
    while (true) {
        cerr << " at L = " << L + 1 << endl;
        cerr << "  ptr:";
        rep(k, K) cerr << " " << ptr[k] + 1;
        cerr << endl;
        cerr << "  len:";
        rep(k, K) cerr << " " << len[k];
        cerr << endl;

        // if any reached the end, finish
        int finished_k = -1;
        rep(k, K) if (active[k]) {
            while (ptr[k] < (int)paths[k].size() && paths[k][ptr[k]].n == 0) {
                ptr[k] += 1;
            }
            if (ptr[k] >= (int)paths[k].size()) {
                finished_k = k;
            }
        }
        if (finished_k != -1) {
            cerr << " shortest path from parent " << parents[finished_k] << endl;
            DP[v] = paths[finished_k];
            return;
        }

        // find special
        ll R = INF;
        rep(k, K) if (active[k]) {
            R = min(R, len[k] + paths[k][ptr[k]].n);
        }
        cerr << "  R = " << R << endl;
        assert(R > L);

        // find min
        int mn_k = -1;
        rep(k, K) if (active[k]) {
            if (mn_k == -1) {
                mn_k = k;
                continue;
            }
            int k_l = paths[k][ptr[k]].l + (L - len[k]);
            int mn_k_l = paths[mn_k][ptr[mn_k]].l + (L - len[mn_k]);
            if (lcp_cmp(k_l, mn_k_l, R - L) < 0) mn_k = k;
        }
        cerr << "  mn_k = " << mn_k + 1 << endl;

        // kill larger
        rep(k, K) if (active[k]) {
            int k_l = paths[k][ptr[k]].l + (L - len[k]);
            int mn_k_l = paths[mn_k][ptr[mn_k]].l + (L - len[mn_k]);
            if (lcp_cmp(k_l, mn_k_l, R - L) > 0) {
                active[k] = false;
                cerr << "  killing " << k + 1 << endl;
            }
        }

        // advance
        rep(k, K) if (active[k]) {
            if (len[k] + paths[k][ptr[k]].n == R) {
                cerr << "  advancing " << k + 1 << endl;
                len[k] += paths[k][ptr[k]].n;
                ptr[k] += 1;
            }
        }
        L = R;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> An >> start >> A;
    start -= 1;
    An = A.size();
    G.resize(N);
    Ginv.resize(N);
    rep(j, M) {
        int u, v, l, n;
        cin >> u >> v >> l >> n;
        u -= 1, v -= 1, l -= 1;
        G[u].push_back({v, l, l + n, n});
        Ginv[v].push_back({u, l, l + n, n});
    }

    ord2pos = suffixarray(A);
    pos2ord.resize(An);
    rep(i, An) pos2ord[ord2pos[i]] = i;
    lcp = Sparse(makelcp(A, ord2pos));

    DP.resize(N);
    DPexist.resize(N);
    canreach.resize(N);
    rep(u, N) dp(u);

    rep(u, N) {
        if (canreach[u]) {
            cout << DP[u].size() + 1 << " " << start + 1;
            for (Edge e : DP[u]) {
                cout << " " << e.v + 1;
            }
            cout << "\n";
        } else {
            cout << "0\n";
        }
    }
}