#include "../../implementation/segment_tree_lazy.cpp"
#include "../test.h"

template <class T, class U, class QU, class UP>
void test_stl(string name, T segt, U neutral, UP update, QU query, int N,
              int M) {
    vector<U> a(N);
    rep(i, N) a[i] = U(random_int(0, INT_MAX));

    cerr << "testing " << name << "... " << flush;
    segt.build(a);
    rep(i, M) {
        {
            int l = random_int(0, N + 1);
            int r = random_int(0, N + 1);
            U ex = neutral;
            repx(i, l, r) query(ex, a[i]);
            U res = segt.query(l, r).x;
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
        "StlSumSum", Stl<NodeSumSum>(), (ll)0, [](ll &a, ll b) { a += b; },
        [](ll &a, ll b) { a += b; }, N, M);
    test_stl(
        "StlSetSum", Stl<NodeSetSum>(), (ll)0, [](ll &a, ll b) { a = b; },
        [](ll &a, ll b) { a += b; }, N, M);
    test_stl(
        "StlSumMin", Stl<NodeSumMin>(), (ll)1e18, [](ll &a, ll b) { a += b; },
        [](ll &a, ll b) { a = min(a, b); }, N, M);
}
