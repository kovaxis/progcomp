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

const ll INF = 1e15;

// find rightmost minimum.
template <class T>
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<pair<T, int>, T>> node;

    Stl() {}
    void build(int N, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * N);
        if (vr == -1) vr = node.size() / 4 - 1;
        node[v] = {{0, -vr}, 0};  // construction
        if (vl != vr) {
            int vm = (vl + vr) / 2;
            build(N, 2 * v, vl, vm);
            build(N, 2 * v + 1, vm + 1, vr);
        }
    }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T& lazy = node[v].second;
        node[2 * v].first.first += lazy;      // update-op & query-op mix
        node[2 * v].second += lazy;           // update-op
        node[2 * v + 1].first.first += lazy;  // update-op & query-op mix
        node[2 * v + 1].second += lazy;       // update-op
        lazy = 0;                             // update-zero
    }

    // apply the update operation to the range [l, r] (inclusive) in O(log N)
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) {
            node[v].first.first += val;  // update-op & query-op mix
            node[v].second += val;       // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        if (l <= vm) update(l, min(r, vm), val, 2 * v, vl, vm);
        if (r >= vm + 1) update(max(l, vm + 1), r, val, 2 * v + 1, vm + 1, vr);
        node[v].first =
            min(node[2 * v].first, node[2 * v + 1].first);  // query-op
    }

    // apply the query operation to the range [l, r] (inclusive) in O(log N)
    pair<T, int> query(int l, int r, int v, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l <= vl && r >= vr) {
            return node[v].first;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        pair<T, int> val = {INF, -vl};  // query-zero
        if (l <= vm)
            val = min(val, query(l, min(r, vm), 2 * v, vl, vm));  // query-op
        if (r >= vm + 1)
            val = min(val, query(max(l, vm + 1), r, 2 * v + 1, vm + 1,
                                 vr));  // query-op
        return val;
    }

    pair<T, int> query(int l, int r) {
        pair<T, int> val = query(l, r, 1);
        val.second = -val.second;
        return val;
    }
};

int N, Q;
string s;
Stl<ll> cost, costb;

int findr(int i, ll thresh) {
    int l = -1, r = i;
    while (l != r) {
        int m = l + (r - l + 1) / 2;
        if (costb.query(m, i).first <= thresh) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

void addb(int i) {
    ll mn = i == N ? INF : costb.query(i + 1, N).first;
    costb.update(0, i, 1);
    int r = findr(i, mn);
    if (r >= 0) cost.update(0, r, 1);
    // cerr << "  added +1 to costb range [0, " << i << "]" << endl;
    // cerr << "  propagated +1 to cost range [0, " << r << "]" << endl;
}

void subb(int i) {
    ll mn = i == N ? INF : costb.query(i + 1, N).first;
    int r = findr(i, mn);
    costb.update(0, i, -1);
    if (r >= 0) cost.update(0, r, -1);
    // cerr << "  added -1 to costb range [0, " << i << "]" << endl;
    // cerr << "  propagated -1 to cost range [0, " << r << "]" << endl;
}

void query(int i, char c) {
    // cerr << endl << "seting s[" << i << "] = " << c << endl;

    pair<ll, int> mn = costb.query(i, N);

    if (s[i] == 'a') cost.update(i + 1, N, -1);
    if (s[i] == 'b') cost.update(0, i, -1);

    if (s[i] == 'b') addb(i);
    if (s[i] == 'c') subb(i);

    s[i] = c;

    if (s[i] == 'a') cost.update(i + 1, N, 1);
    if (s[i] == 'b') cost.update(0, i, 1);

    if (s[i] == 'b') subb(i);
    if (s[i] == 'c') addb(i);

    /*cerr << "i:     " << endl;
    rep(i, N + 1) cerr << i << " ";
    cerr << endl << "cost:  " << endl;
    rep(i, N + 1) cerr << cost.query(i, i).first << " ";
    cerr << endl << "costb: " << endl;
    rep(i, N + 1) cerr << costb.query(i, i).first << " ";
    cerr << endl;*/
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q >> s;
    N = s.size();

    cost.build(N + 1), costb.build(N + 1);
    rep(i, N) {
        char c = s[i];
        s[i] = '_';
        query(i, c);
    }

    rep(q, Q) {
        int i;
        char c;
        cin >> i >> c;
        query(i - 1, c);
        cout << cost.query(0, N).first << "\n";
    }
}
