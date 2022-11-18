#include "../../implementation/segment_tree_lazy.cpp"
#include "../test.h"

struct NodeSumSum {
    ll x, lazy;

    NodeSumSum() : x(neutral()), lazy(0) {}
    NodeSumSum(ll x_) : NodeSumSum() { x = x_; }
    NodeSumSum(NodeSumSum &l, NodeSumSum &r) : NodeSumSum() { refresh(l, r); }
    void refresh(NodeSumSum &l, NodeSumSum &r) { x = merge(l.x, r.x); }

    void update(ll val, int l, int r) { x += val * (r - l), lazy += val; }
    ll take() {
        ll z = 0;
        swap(lazy, z);
        return z;
    }

    ll query() { return x; }
    static ll neutral() { return 0; }
    static ll merge(ll l, ll r) { return l + r; }
};

struct NodeSetSum {
    ll x, lazy;

    NodeSetSum() : x(neutral()), lazy(INT64_MIN) {}
    NodeSetSum(ll x_) : NodeSetSum() { x = x_; }
    NodeSetSum(NodeSetSum &l, NodeSetSum &r) : NodeSetSum() { refresh(l, r); }
    void refresh(NodeSetSum &l, NodeSetSum &r) { x = merge(l.x, r.x); }

    void update(ll val, int l, int r) {
        if (val != INT64_MIN)
            x = val * (r - l), lazy = val;
    }
    ll take() {
        ll z = INT64_MIN;
        swap(lazy, z);
        return z;
    }

    ll query() { return x; }
    static ll neutral() { return 0; }
    static ll merge(ll l, ll r) { return l + r; }
};

struct NodeSumMin {
    ll x, lazy;

    NodeSumMin() : x(neutral()), lazy(0) {}
    NodeSumMin(ll x_) : NodeSumMin() { x = x_; }
    NodeSumMin(NodeSumMin &l, NodeSumMin &r) : NodeSumMin() { refresh(l, r); }
    void refresh(NodeSumMin &l, NodeSumMin &r) { x = merge(l.x, r.x); }

    void update(ll val, int l, int r) { x += val, lazy += val; }
    ll take() {
        ll z = 0;
        swap(lazy, z);
        return z;
    }

    ll query() { return x; }
    static ll neutral() { return 1e18; }
    static ll merge(ll l, ll r) { return min(l, r); }
};

template <class T, class U, class QU, class UP, class BU>
void test_stl(string name, T segt, U neutral, UP update, QU query, BU build, int N,
              int M) {
    vector<U> a(N);
    rep(i, N) a[i] = U(random_int(0, INT_MAX));

    cerr << "testing " << name << "... " << flush;
    build(segt, a);
    rep(i, M) {
        {
            int l = random_int(0, N + 1);
            int r = random_int(0, N + 1);
            U ex = neutral;
            repx(i, l, r) query(ex, a[i]);
            U res = segt.query(l, r);
            if (res != ex) {
                cerr << "query for [" << l << ", " << r << ") failed: expected "
                     << ex << ", got " << res << endl;
                assert(res == ex);
            }
        }

        {
            int l = random_int(0, N + 1);
            int r = random_int(0, N + 1);
            U upd = (U)random_int(0, INT_MAX);
            repx(i, l, r) update(a[i], upd);
            segt.update(l, r, upd);
        }
    }
    cerr << "ok" << endl;
}

int main() {
    int N = 10000;
    int M = 10000;

    test_stl(
        "Stl3SumSum", Stl3<ll>(), (ll)0, [](ll &a, ll b) { a += b; },
        [](ll &a, ll b) { a += b; }, [](auto &st, auto &a) { st.reset(a.size()); rep(i, a.size()) st.update(i, i+1, a[i]); }, N, M);
    test_stl(
        "StlSumSum", Stl<ll, NodeSumSum>(), (ll)0, [](ll &a, ll b) { a += b; },
        [](ll &a, ll b) { a += b; }, [](auto &st, auto &a) { st.build(a); }, N, M);
    test_stl(
        "StlSetSum", Stl<ll, NodeSetSum>(), (ll)0, [](ll &a, ll b) { a = b; },
        [](ll &a, ll b) { a += b; }, [](auto &st, auto &a) { st.build(a); }, N, M);
    test_stl(
        "StlSumMin", Stl<ll, NodeSumMin>(), (ll)1e18, [](ll &a, ll b) { a += b; },
        [](ll &a, ll b) { a = min(a, b); }, [](auto &st, auto &a) { st.build(a); }, N, M);
}
