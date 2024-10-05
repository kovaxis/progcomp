#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

ostream &operator<<(ostream &s, vector<int> &a) {
    for (int x : a) s << x << " ";
    return s;
}

int N, M;
vector<int> raw[2], against[2], A, B;
map<int, int> comp;
vector<int> decomp;

int k0, k1;
double ans;

void addcomp(int x) {
    if (x < 1) return;
    comp[x] = 0;
}

double eval(int i, int j) {
    return ((double)A[j] * B[i] - (double)A[i] * B[j]) / (-A[i] + A[j]);
}

void rec(int il, int ir, int jl, int jr) {
    if (il >= ir) return;
    int i = (il + ir) / 2;
    int jopt = jl;
    double vopt = eval(i, jopt);
    repx(j, jl, jr) {
        double v = eval(i, j);
        if (v < vopt) jopt = j, vopt = v;
    }
    ans = min(ans, vopt);
    rec(il, i, jl, jopt + 1);
    rec(i + 1, ir, jopt, jr);
}

double solve() {
    cerr << "A: " << A << endl;
    cerr << "B: " << B << endl;

    for (k0 = 0; k0 < N; k0++)
        if (A[k0] >= 0) break;
    for (k1 = 0; k1 < N; k1++)
        if (A[k1] > 0) break;

    ans = B[k0];
    rec(0, k0, k1, N);

    return ans / M;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    rep(l, 2) {
        int n;
        cin >> n;
        raw[l].resize(n);
        rep(i, n) cin >> raw[l][i];
    }

    rep(l, 2) {
        sort(raw[l].begin(), raw[l].end());
        for (int x : raw[l]) addcomp(x - 1), addcomp(x), addcomp(x + 1);
    }
    N = comp.size();
    for (auto &[x, v] : comp) {
        v = decomp.size();
        decomp.push_back(x);
    }

    rep(l, 2) {
        against[l].resize(N);
        rep(i, N) {
            against[l][i] += lower_bound(raw[l].begin(), raw[l].end(), decomp[i]) - raw[l].begin();
            against[l][i] -= raw[l].end() - upper_bound(raw[l].begin(), raw[l].end(), decomp[i]);
        }
    }

    ll onevtwo = 0;
    for (int x : raw[0]) onevtwo += against[1][comp[x]];
    if (onevtwo < 0) swap(raw[0], raw[1]), swap(against[0], against[1]);

    A = against[0], B = against[1], M = raw[1].size();
    double a = (1 + solve()) / 2;

    A = against[1], B = against[0], M = raw[0].size();
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    rep(i, N) A[i] *= -1, B[i] *= -1;
    double b = (1 - solve()) / 2;

    cout << fixed << setprecision(12) << a << endl
         << b << endl;
}
