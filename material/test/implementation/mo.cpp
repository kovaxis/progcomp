#include "../../implementation/mo.cpp"
#include "../test.h"

template <class A, class R, class G, class T, class OP>
void test_mo(string name, A add, R remove, G get, T neutral, OP op, int N,
             int M) {
    vector<T> a(N);
    rep(i, N) a[i] = T(random_int(0, INT_MAX));

    cerr << "testing " << name << "... " << flush;
    vector<Query> queries(M);
    vector<T> exans(M);
    vector<T> ans(M);
    rep(i, M) {
        int l, r;
        do {
            l = random_int(0, N + 1);
            r = random_int(0, N + 1);
        } while (l > r);
        queries[i] = {l, r, i};

        T ex = neutral;
        repx(j, l, r) op(ex, a[j]);
        exans[i] = ex;
    }
    mo(
        queries, ans, [&](int i) { add(a, i); }, [&](int i) { remove(a, i); },
        [&]() { return get(a); });
    rep(i, M) { assert(ans[i] == exans[i]); }
    cerr << "ok" << endl;
}

int main() {
    ll sm = 0;
    test_mo(
        "sum",
        [&](vector<ll> &a, int i) {
            // cerr << "  adding " << i << endl;
            sm += a[i];
        },
        [&](vector<ll> &a, int i) {
            // cerr << "  removing " << i << endl;
            sm -= a[i];
        },
        [&](vector<ll> &a) { return sm; }, (ll)0,
        [&](ll &acc, ll a) { acc += a; }, 1e4, 1e4);
}
