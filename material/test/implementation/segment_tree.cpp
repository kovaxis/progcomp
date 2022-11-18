#include "../../implementation/segment_tree.cpp"
#include "../test.h"

struct NodeSum {
    ll x;

    NodeSum() : x(neutral()) {}
    NodeSum(ll x) : x(x) {} // optional
    NodeSum(NodeSum &l, NodeSum &r) { refresh(l, r); }
    void refresh(NodeSum &l, NodeSum &r) { x = merge(l.x, r.x); }

    ll query() { return x; }
    void update(ll a) { x = a; }
    static ll neutral() { return 0; }
    static ll merge(ll l, ll r) { return l + r; }
};

struct NodeMin {
    ll x;

    NodeMin() : x(neutral()) {}
    NodeMin(ll x) : x(x) {} // optional
    NodeMin(NodeMin &l, NodeMin &r) { refresh(l, r); }
    void refresh(NodeMin &l, NodeMin &r) { x = merge(l.x, r.x); }

    ll query() { return x; }
    void update(ll a) { x = a; }
    static ll neutral() { return 1e18; }
    static ll merge(ll l, ll r) { return min(l, r); }
};

struct NodeMax {
    ll x;

    NodeMax() : x(neutral()) {}
    NodeMax(ll x) : x(x) {} // optional
    NodeMax(NodeMax &l, NodeMax &r) { refresh(l, r); }
    void refresh(NodeMax &l, NodeMax &r) { x = merge(l.x, r.x); }

    ll query() { return x; }
    void update(ll a) { x = a; }
    static ll neutral() { return -1e18; }
    static ll merge(ll l, ll r) { return max(l, r); }
};

template <class T, class U, class OP, class B>
void test_segt(string name, T segt, U neutral, OP op, B build, int N, int M) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<U> a(N);
    rep(i, N) a[i] = U((int32_t)rng());

    cerr << "testing " << name << "... " << flush;
    build(segt, a);
    rep(i, M) {
        int l = rng() % (N + 1);
        int r = rng() % (N + 1);
        U ex = neutral;
        repx(j, l, r) op(ex, a[j]);
        U res = segt.query(l, r);
        assert(res == ex);

        int j = rng() % N;
        a[j] = (U)rng();
        segt.update(j, a[j]);
    }
    cerr << "ok" << endl;
}

int main() {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int N = 10000;
    int M = 10000;

    test_segt(
        "St3Sum", St3<ll>(), (ll)0, [](ll &a, ll b) { a += b; }, [](auto &st, auto &a) { st.reset(a.size()); rep(i, a.size()) st.update(i, a[i]); }, N, M);
    test_segt(
        "StSum", St<ll, NodeSum>(), (ll)0, [](ll &a, ll b) { a += b; }, [](auto &st, auto &a) { st.build(a); }, N, M);
    test_segt(
        "StMax", St<ll, NodeMax>(), (ll)-1e18, [](ll &a, ll b) { a = max(a, b); }, [](auto &st, auto &a) { st.build(a); }, N, M);
    test_segt(
        "StMin", St<ll, NodeMin>(), (ll)1e18, [](ll &a, ll b) { a = min(a, b); }, [](auto &st, auto &a) { st.build(a); }, N, M);
}
