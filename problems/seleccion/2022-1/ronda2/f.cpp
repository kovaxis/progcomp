#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const ll MOD = 1e9 + 7;

ll N, M, B, K;
vector<ll> a, c, p10;

void multmatrix(vector<ll>& a, const vector<ll>& l, const vector<ll>& r,
                ll MOD) {
    static vector<ll> tmp;
    int N = l.size();
    tmp.resize(N);
    rep(i, N) {
        ll x = 0;
        rep(j, N) x += l[j] * r[(i - j + N) % N] % MOD;
        tmp[i] = x % MOD;
    }
    swap(a, tmp);
}

void binexp(vector<ll>& a, ll m, ll M) {
    // neutral element
    vector<ll> res(a.size());
    res[0] = 1;
    while (m) {
        if (m & 1) multmatrix(res, res, a, M);  // multiplication
        multmatrix(a, a, a, M);                 // multiplication
        m >>= 1;
    }
    a = res;
}

void printmatrix(const vector<ll>& a) {
    int N = a.size();
    rep(i, N) rep(j, M) {
        cerr << a[(i - j + N) % N];
        if (j == M - 1)
            cerr << endl;
        else
            cerr << " ";
    }
}

void doit(vector<ll>& ans, ll x, int m) {
    vector<ll> mat(M);
    rep(i, M) mat[i * p10[m] % M] += c[i];
    cerr << "  base matrix:" << endl;
    printmatrix(mat);

    binexp(mat, x, MOD);
    cerr << "  exponentiated matrix:" << endl;
    printmatrix(mat);

    multmatrix(ans, ans, mat, MOD);
    cerr << "  overall answer matrix:" << endl;
    printmatrix(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> B >> K >> M;
    a.resize(N);
    rep(i, N) cin >> a[i];
    c.resize(M);
    rep(i, N) c[a[i] % M] += 1;

    p10.resize(M + 1);
    p10[0] = 1;
    rep(i, M) p10[i + 1] = p10[i] * 10 % M;

    vector<int> seen(M, -1);
    int rfrom, rto;
    rep(i, M + 1) {
        if (seen[p10[i]] != -1) {
            rfrom = seen[p10[i]];
            rto = i;
            break;
        }
        seen[p10[i]] = i;
    }
    cerr << "mod10 = " << rfrom << " / " << rto << endl;

    vector<ll> ans(M);
    ans[0] = 1;
    rep(m, rfrom) { doit(ans, 1, m); }
    repx(m, rfrom, rto) {
        // get amount of blocks with 10^m as multiplier
        int P = rto - rfrom;
        ll x = (B - rfrom) / P + (m < (B - rfrom) % P);
        cerr << x << " blocks with 10^" << m << " = " << p10[m]
             << " as multiplier" << endl;
        doit(ans, x, m);
    }

    cout << ans[K] << endl;
}
