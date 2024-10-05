// https://codeforces.com/contest/1556/problem/G

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= int(a); i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

struct Dsu {
    vector<int> p, r;

    // initialize the disjoint-set-union to all unitary sets
    Dsu(int N = 0) : p(N), r(N) { rep(i, N) p[i] = i; }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two sets that `i` and `j` belong to
    void unite(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        if (r[i] > r[j]) swap(i, j);
        if (r[i] == r[j]) r[j] += 1;
        p[i] = j;
    }
};

struct Query {
    char ty;
    ll l, r;
    bool ans;
};

struct Seg {
    ll l, r;
    int t;
};

struct Conn {
    int ui, vlo, vhi;
};

struct Op {
    int ui, vi;
};

pair<int, int> split(ll x) {
    return {x & ((1ll << 32) - 1), x >> 32};
}

ll join(int lo, int hi) {
    return ll(lo) | (ll(hi) << 32);
}

int N, M;
vector<Query> B;
vector<Seg> C, D;
vector<vector<Op>> E;
Dsu F;

void genseg(int t, ll l, ll r, ll L, ll R) {
    if (l >= R || r <= L || R <= L) return;
    if (l >= L && r <= R) {
        cerr << "  generating atom " << l << " " << r << endl;
        C.push_back({l, r, t});
    } else {
        ll m = (l + r) / 2;
        genseg(t, l, m, L, R);
        genseg(t, m, r, L, R);
    }
}

int seg_at(ll i, int l = 0, int r = 1e9) {
    r = min(r, int(D.size())) - 1;
    while (l != r) {
        int m = (l + r + 1) / 2;
        if (D[m].l <= i) l = m;
        else r = m - 1;
    }
    return l;
}

template <class T, class K>
void radsort(vector<T> &v, K key) {
    vector<T> u(v.size());
    rep(b, 4) {
        int cnt[256];
        rep(c, 256) cnt[c] = 0;
        rep(i, v.size()) cnt[(key(v[i]) >> (b * 8)) & 0xFF] += 1;
        repx(c, 1, 256) cnt[c] += cnt[c - 1];
        invrep(i, v.size()) u[--cnt[(key(v[i]) >> (b * 8)) & 0xFF]] = v[i];
        swap(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    B.resize(M);
    rep(t, M) {
        string ty;
        ll l, r;
        cin >> ty >> l >> r;
        if (ty[0] == 'b') r += 1;
        B[t] = {ty[0], l, r};
    }

    rep(t, M) {
        if (B[t].ty == 'b') {
            cerr << "generating segment " << B[t].l << " " << B[t].r << endl;
            genseg(t, 0, 1ll << N, B[t].l, B[t].r);
        }
    }

    D = C;
    sort(D.begin(), D.end(), [](auto a, auto b) {
        return a.l < b.l;
    });

    D.insert(D.begin(), {0, 0, 0});
    D.push_back({1ll << N, 1ll << N, 0});
    C.clear();
    rep(i, D.size() - 1) {
        cerr << "generating segment " << D[i].r << " " << D[i + 1].l << endl;
        genseg(M, 0, 1ll << N, D[i].r, D[i + 1].l);
    }
    D.pop_back();
    D.erase(D.begin());
    D.insert(D.end(), C.begin(), C.end());

    sort(D.begin(), D.end(), [](auto a, auto b) {
        return a.l < b.l;
    });

    E.resize(M + 1);
    rep(b, N) {
        int l = 0, r = 0;
        ll delta = 1ll << b;
        rep(i, D.size()) {
            int vi;
            if (D[i].l & delta) {
                // left
                ll v = D[i].l - delta;
                while (v >= D[l].r) l += 1;
                vi = l;
            } else {
                // right
                ll v = D[i].l + delta;
                while (v >= D[r].r) r += 1;
                vi = r;
            }
            if (make_pair(D[vi].r - D[vi].l, vi) > make_pair(D[i].r - D[i].l, i)) {
                cerr << "connection between " << i << "/" << D.size() << " and " << vi << "/" << D.size() << ", [" << D[i].l << ", " << D[i].r << ") and [" << D[vi].l << ", " << D[vi].r << ")" << endl;
                E[min(D[i].t, D[vi].t)].push_back({i, vi});
            }
        }
    }

    F = {int(D.size())};

    invrep(t, M + 1) {
        for (Op op : E[t]) {
            // connection
            F.unite(op.ui, op.vi);
        }
        if (t < M && B[t].ty == 'a') {
            // question
            Query &q = B[t];
            int ui = seg_at(q.l);
            int vi = seg_at(q.r);
            q.ans = (F.find(ui) == F.find(vi));
        }
    }

    rep(t, M) {
        if (B[t].ty == 'a') cout << B[t].ans << "\n";
    }

    // |-------------------------------|
    // |---------------|---------------|
    // |-------|-------|-------|-------|
    // |---|---|---|---|---|---|---|---|
    // |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
}
