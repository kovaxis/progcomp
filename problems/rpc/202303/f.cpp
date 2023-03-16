#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (ll i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

struct P {
    ll x, y;

    P(ll x, ll y) : x(x), y(y) {}
    P() : x(0), y(0) {}

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }

    P rot() const { return {-y, x}; }

    ll operator*(P r) const { return x * r.x + y * r.y; }
    ll operator/(P r) const { return rot() * r; }

    friend ostream &operator<<(ostream &s, P p) {
        return s << p.x << " " << p.y;
    }

    friend istream &operator>>(istream &s, P &p) {
        return s >> p.x >> p.y;
    }
};

vector<P> convex_hull(vector<P> &ps) {
    int N = ps.size(), n = 0, k = 0;
    if (N <= 2) return ps;
    rep(i, N) if (make_pair(ps[i].y, ps[i].x) < make_pair(ps[k].y, ps[k].x)) k = i;
    swap(ps[k], ps[0]);
    sort(++ps.begin(), ps.end(), [&](P l, P r) {
        ll x = (r - l) / (ps[0] - l), d = (r - l) * (ps[0] - l);
        return x > 0 || x == 0 & d < 0;
    });
    vector<P> H;
    for (P p : ps) {
        while (n >= 2 && (H[n - 1] - p) / (H[n - 2] - p) >= 0) H.pop_back(), n--;
        H.push_back(p), n++;
    }
    return H;
}

const ll INF = 2e9;

struct R {
    ll n, d;

    bool operator<(R r) const {
        // n1 / d1 < n2 / d2
        // n1 * d2 < n2 * d1
        return n * r.d < r.n * d;
    }

    bool operator==(R r) const { return n * r.d == r.n * d; }
    bool operator!=(R r) const { return n * r.d != r.n * d; }
    R operator-() const { return {-n, d}; }
};

struct Query {
    int l, r, idx;
};

int N;
P S, D, E;
vector<P> A, up, dn, lt, rt;
vector<int> L, R, invL, invR;
vector<Query> Q;
ll ans;

void solve() {
    N = A.size();
    L.resize(N), R.resize(N);
    rep(i, N) L[i] = i, R[i] = i;
    sort(L.begin(), L.end(), [](int i, int j) {
        ll x = (A[i] - S) / (A[j] - S), d = (A[i] - S) * (A[j] - A[i]);
        return x < 0 || x == 0 && d < 0;
    });
    sort(R.begin(), R.end(), [](int i, int j) {
        ll x = (A[i] - E) / (A[j] - E), d = (A[i] - E) * (A[j] - A[i]);
        return x < 0 || x == 0 && d > 0;
    });

    invL.resize(N), invR.resize(N);
    rep(i, N) invL[L[i]] = i, invR[R[i]] = i;

    cerr << "L:";
    rep(i, N) cerr << " " << L[i] + 1;
    cerr << endl;
    cerr << "R:";
    rep(i, N) cerr << " " << R[i] + 1;
    cerr << endl;

    Q.resize(N);
    rep(i, N) Q[i].idx = i;
    rep(j, N) Q[L[j]].l = j;
    rep(j, N) Q[R[j]].r = j;

    int qn = Q.size(), qb = sqrt(int(Q.size()));
    int l = N, r = -1;
    ll acc = 0;
    sort(Q.begin(), Q.end(), [&](Query a, Query b) {
        return make_pair(a.l / qb, a.r) < make_pair(b.l / qb, b.r);
    });
    for (auto q : Q) {
        cerr << "point " << A[q.idx] << " is on range [" << q.l << ", " << q.r << "]" << endl;
        cerr << "starting from range [" << l << ", " << r << "]" << endl;
        while (r < q.r) {
            r++;
            // add the `r` line
            cerr << "moving R line to point " << R[r] + 1 << " = " << A[R[r]] << endl;
            if (invL[R[r]] >= l)
                acc += 1;
            cerr << "now there are " << acc << " points" << endl;
        }
        while (l > q.l) {
            l--;
            // add the `l` line
            cerr << "moving L line to point " << L[l] + 1 << " = " << A[L[l]] << endl;
            if (invR[L[l]] <= r)
                acc += 1;
            cerr << "now there are " << acc << " points" << endl;
        }
        while (r > q.r) {
            // remove the `r` line
            cerr << "moving R line from previous point " << R[r] + 1 << " = " << A[R[r]] << endl;
            if (invL[R[r]] >= l)
                acc -= 1;
            cerr << "now there are " << acc << " points" << endl;
            r--;
        }
        while (l < q.l) {
            // remove the `l` line
            cerr << "moving L line from previous point " << L[l] + 1 << " = " << A[L[l]] << endl;
            if (invR[L[l] <= r])
                acc -= 1;
            cerr << "now there are " << acc << " points" << endl;
            l++;
        }
        cerr << acc << " points in triangle defined by point " << A[L[l]] << " = " << A[R[r]] << endl;
        ans += acc - 1;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> S.x >> S.y >> E.x >> E.y;
    D = E - S;
    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i].x >> A[i].y;

    rep(i, N) {
        P d = A[i] - S;
        if (d / D == 0) {
            if (d * D > 0) rt.push_back(A[i]);
            else lt.push_back(A[i]);
        } else {
            if (d / D > 0) dn.push_back(A[i]);
            else up.push_back(A[i]);
        }
    }

    cerr << lt.size() << " left, " << rt.size() << " right, " << up.size() << " up, " << dn.size() << " down" << endl;

    ans += (ll(lt.size()) - 1) * ll(lt.size()) / 2;
    ans += (ll(rt.size()) - 1) * ll(rt.size()) / 2;

    A = up;
    solve();
    A = dn;
    swap(S, E);
    D = {-D.x, -D.y};
    solve();

    cout << ans << endl;
}
