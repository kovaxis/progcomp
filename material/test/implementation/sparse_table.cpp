#include "../../implementation/sparse_table.cpp"
#include "../test.h"

Sparse<int> re;
vector<int> na;

void query(int l, int r) {
    if (l == r) return;
    if (l > r) swap(l, r);
    int ex = na[l];
    repx(i, l, r) ex = max(ex, na[i]);
    int out = re.query(l, r);
    assert(out == ex);
}

int main() {
    int N = 1e4;
    int M = 1e4;
    na.resize(N);
    rep(i, N) na[i] = random_int(-1e9, 1e9);
    re.reset(N);
    rep(i, N) re.set(i, na[i]);
    re.init();

    rep(j, M) query(random_int(0, N), random_int(0, N));
    cerr << "all ok" << endl;
}
