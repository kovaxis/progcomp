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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<P> A(N), A4(4 * N);
    rep(i, N) cin >> A[i].x >> A[i].y;

    rep(i, N) {
        A4[i + 0 * N] = A[i] + P(1, 0);
        A4[i + 1 * N] = A[i] + P(-1, 0);
        A4[i + 2 * N] = A[i] + P(0, 1);
        A4[i + 3 * N] = A[i] + P(0, -1);
    }

    vector<P> H1 = convex_hull(A);
    ll ans = 0;
    if (H1.size() == 2 && abs((H1[1] - H1[0]).x) == abs((H1[1] - H1[0]).y))
        ans += 1;

    vector<P> H = convex_hull(A4);
    rep(i, H.size()) {
        // cerr << "H[" << i + 1 << "] = " << H[i].x << " " << H[i].y << endl;
        int j = (i + 1) % H.size();
        P d = H[i] - H[j];
        ans += max(abs(d.x), abs(d.y));
    }
    cout << ans << endl;
}
