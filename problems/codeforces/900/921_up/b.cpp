#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Node {
    ll asum, bsum, abmul;
};

struct Upd {
    ll a, b;
};

struct Stl {
    int n;
    vector<Node> a;
    vector<Upd> b;

    Node qneut() { return {0, 0, 0}; }
    Upd uneut() { return {0, 0}; }
    Node merge(Node x, Node y) {
        return {x.asum + y.asum, x.bsum + y.bsum, x.abmul + y.abmul};
    }
    void upd(int v, Upd x, int l, int r) {
        // apply a-upd
        a[v].abmul += a[v].bsum * x.a;
        a[v].asum += (r - l) * x.a;

        // apply b-upd
        a[v].abmul += a[v].asum * x.b;
        a[v].bsum += (r - l) * x.b;

        // lazy upd
        b[v].a += x.a;
        b[v].b += x.b;
    }

    Stl() {}
    Stl(int n) : n(n), a(4 * n, qneut()), b(4 * n, uneut()) {}

    void push(int v, int vl, int vm, int vr) {
        upd(2 * v, b[v], vl, vm);
        upd(2 * v + 1, b[v], vm, vr);
        b[v] = uneut();
    }

    // compute the query operation for the range [l, r)
    Node query(int l, int r, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l <= vl && r >= vr) return a[v];
        if (l >= vr || r <= vl) return qneut();
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr));
    }

    // apply update operation to range [l, r)
    void update(int l, int r, Upd x, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) upd(v, x, vl, vr);
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, x, 2 * v, vl, vm);
            update(l, r, x, 2 * v + 1, vm, vr);
            a[v] = merge(a[2 * v], a[2 * v + 1]);
        }
    }
};

struct Query {
    char ty;
    int x, v, l, r;
};

int N, M, Qn;
vector<int> X, V;
vector<Query> Q;
Stl A;
set<int> P;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Qn;
    X.resize(M), V.resize(M);
    rep(j, M) cin >> X[j];
    rep(j, M) X[j] -= 1;
    rep(j, M) cin >> V[j];
    rep(j, M) {
        Q.push_back({'u', X[j], V[j], 0, 0});
    }
    rep(_, Qn) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, v;
            cin >> x >> v;
            x -= 1;
            Q.push_back({'u', x, v, 0, 0});
        } else if (ty == 2) {
            int l, r;
            cin >> l >> r;
            l -= 1;
            Q.push_back({'q', 0, 0, l, r});
        }
    }

    A = {N};
    rep(i, N) {
        A.update(i, i + 1, {0, N - i - 1});
    }

    P.insert(-1);
    P.insert(N);

    for (Query q : Q) {
        if (q.ty == 'u') {
            // update
            int left = *(--P.lower_bound(q.x));
            int right = *P.lower_bound(q.x);
            Node me = A.query(q.x, q.x + 1);
            A.update(q.x, right, {q.v - me.asum, 0});
            A.update(left + 1, q.x + 1, {0, -me.bsum});
            P.insert(q.x);
        } else {
            // question
            cout << A.query(q.l, q.r).abmul << "\n";
        }
    }
}
