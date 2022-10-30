#include "../../implementation/segment_tree.cpp"
#include "../test.h"

template <class T, class U, class OP>
void test_segt(string name, T segt, U neutral, OP op, int N, int M) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<U> a(N);
    rep(i, N) a[i] = U((int32_t)rng());

    cerr << "testing " << name << "... " << flush;
    segt.build(a);
    rep(i, M) {
        int l = rng() % (N + 1);
        int r = rng() % (N + 1);
        U ex = neutral;
        repx(j, l, r) op(ex, a[j]);
        U res = segt.query(l, r).x;
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
        "StSum", St<NodeSum>(), (ll)0, [](ll &a, ll b) { a += b; }, N, M);
    test_segt(
        "StMax", St<NodeMax>(), (ll)-1e18, [](ll &a, ll b) { a = max(a, b); }, N, M);
    test_segt(
        "StMin", St<NodeMin>(), (ll)1e18, [](ll &a, ll b) { a = min(a, b); }, N, M);
}
