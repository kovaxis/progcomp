#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// gets the prime factorization of a number in O(sqrt(n))
void factorize(vector<pair<ll, int>> &facts, ll x) {
    ll k = 2;
    while (x > 1) {
        if (k * k > x) {
            facts.push_back({x, 1});
            break;
        }
        int n = 0;
        while (x % k == 0) x /= k, n++;
        if (n > 0) facts.push_back({k, n});
        k += 1;
    }
}

// iterate over all divisors of a number.
//
// divisor count upper bound: n^(1.07 / ln ln n)
template <class OP>
void divisors(ll x, OP op) {
    vector<pair<ll, int>> facts;
    factorize(facts, x);
    vector<int> f(facts.size());
    while (true) {
        ll y = 1;
        rep(i, f.size()) rep(j, f[i]) y *= facts[i].first;
        op(y);

        int i = 0;
        while (i < f.size()) {
            f[i] += 1;
            if (f[i] > facts[i].second)
                f[i++] = 0;
            else
                break;
        }
        if (i == f.size()) break;
    }
}

struct Node {
    // answer for this range
    ll ans;
    // minimum B that is divided by key
    map<int, int> minb;
    // lazy value to set
    ll lazy;

    Node() {}
    Node(ll b) : lazy(INT64_MIN) {
        divisors(b, [&](ll d) {
            minb[d] = b;
        });
        // assuming a = 1
        ans = b;
    }
    Node(Node &l, Node &r) : lazy(INT64_MIN) {
        minb = l.minb;
        for (auto [d, b] : r.minb) {
            if (minb.count(d) == 0) minb[d] = b;
            else if (b < minb[d]) minb[d] = b;
        }

        refresh(l, r);
    }

    void refresh(Node &l, Node &r) {
        ans = merge(l.ans, r.ans);
    }

    ll query() { return ans; }
    static ll neutral() { return 1e18; }
    static ll merge(ll l, ll r) { return min(l, r); }

    void update(ll val, int l, int r) {
        if (val != INT64_MIN) {
            // find minimum answer
            ans = neutral();
            divisors(val, [&](ll d) {
                if (minb.count(d) != 0) ans = merge(ans, (minb[d] / d) * (val / d));
            });

            lazy = val;
        }
    }
    ll take() {
        ll z = lazy;
        lazy = INT64_MIN;
        return z;
    }
};

template <class T, class Node>
struct Stl {
    vector<Node> node;

    void reset(int N) { node.assign(4 * N, {}); }

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size()), vr = vr == -1 ? node.size() / 4 : vr;
        if (vr - vl == 1) {
            node[v] = {a[vl]}; // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = {node[2 * v], node[2 * v + 1]}; // query op
    }

    void push(int v, int vl, int vm, int vr) {
        T lazy = node[v].take();
        node[2 * v].update(lazy, vl, vm);
        node[2 * v + 1].update(lazy, vm, vr);
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].query();
        T val = Node::neutral(); // neutral element
        if (l >= vr || r <= vl) return val;
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return Node::merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // query op
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) {
            node[v].update(val, vl, vr); // update-op & query-op mix
            return;
        }
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        update(l, r, val, 2 * v, vl, vm);
        update(l, r, val, 2 * v + 1, vm, vr);
        node[v].refresh(node[2 * v], node[2 * v + 1]); // query-op & update-zero
    }
};

int N, Q;
vector<ll> a, b;

Stl<ll, Node> stl;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    a.resize(N), b.resize(N);
    rep(i, N) cin >> a[i];
    rep(i, N) cin >> b[i];

    stl.build(b);
    rep(i, N) stl.update(i, i + 1, a[i]);

    rep(q, Q) {
        int t, l, r;
        cin >> t >> l >> r;
        l -= 1;

        if (t == 1) {
            // assign
            ll x;
            cin >> x;

            stl.update(l, r, x);
        } else if (t == 2) {
            // query
            cout << stl.query(l, r) << "\n";
        }
    }
}
