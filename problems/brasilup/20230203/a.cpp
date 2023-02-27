#pragma GCC optimize("O2")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

const int INF = 1e9;

int N;
vector<int> A, B;

struct Idx {
    int16_t n, h;
};

int dist(Idx I, Idx J) {
    if (I.n >= N && J.n >= N) return 0;
    if (I.n >= N) return B[J.n + 1] - J.h;
    if (J.n >= N) return A[I.n + 1] - I.h;
    return min(A[I.n + 1] - I.h, B[J.n + 1] - J.h);
}

Idx adv(const vector<int> &A, Idx I, int steps) {
    if (I.n >= N) return I;
    cerr << "doing " << steps << " steps with max of " << A[I.n + 1] - I.h << " steps" << endl;
    assert(steps <= A[I.n + 1] - I.h);
    if (steps == A[I.n + 1] - I.h) {
        I.n += 1;
    }
    I.h += steps;
    return I;
}

int dp(Idx I, Idx J, bool k);

int dpinner(Idx I, Idx J, bool k) {
    cerr << "computing " << I.n << "." << I.h << " and " << J.n << "." << J.h << " with skip = " << k << endl;

    if (J.n >= N) return A[N] - I.h;

    int d = dist(I, J);
    cerr << "  advancing by " << d << endl;

    int adv_b = INF, adv_both = INF, skip = INF;
    cerr << "computing adv_b for " << I.n << "." << I.h << " and " << J.n << "." << J.h << " with skip = " << k << " and d = " << d << endl;
    if (J.n < N) adv_b = d + dp(I, adv(B, J, d), true);
    cerr << "computing skip for " << I.n << "." << I.h << " and " << J.n << "." << J.h << " with skip = " << k << " and d = " << d << endl;
    if (J.n < N - 1 && J.h == B[J.n] && k) skip = dp(I, adv(B, J, B[J.n + 1] - B[J.n]), false);
    cerr << "computing adv_both for " << I.n << "." << I.h << " and " << J.n << "." << J.h << " with skip = " << k << " and d = " << d << endl;
    if (I.n < J.n) adv_both = d + dp(adv(A, I, d), adv(B, J, d), true);

    return min(adv_both, min(adv_b, skip));
}

vector<int> dpmem[2];
int dp(Idx I, Idx J, bool k) {
    int code;
    if (I.h == A[I.n]) code = (J.h * 1009) + (I.n) + (10900000);
    else code = (I.h * 1009) + (J.n);
    if (dpmem[k][code] != -1) return dpmem[k][code];
    return dpmem[k][code] = dpinner(I, J, k);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    A.resize(N + 1), B.resize(N + 1);
    rep(i, N) cin >> A[i + 1];
    rep(i, N) cin >> B[i + 1];
    rep(i, N) A[i + 1] += A[i];
    rep(i, N) B[i + 1] += B[i];

    rep(k, 2) dpmem[k].assign(3e7, -1);

    cout << dp({0, 0}, {0, 0}, false) << endl;
}
