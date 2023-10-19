// https://codeforces.com/problemset/problem/166/B

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

struct P {
    ll x, y;

    P operator-(P r) { return {x - r.x, y - r.y}; }

    P rot() const { return {-y, x}; }
    ll operator*(P r) const { return x * r.x + y * r.y; }
    ll operator%(P r) const { return rot() * r; }
    ll left(P a, P b) { return (b - a) % (*this - a); }
};

int N, M;
vector<P> A, B;

ll in_convex(const vector<P> &p, P q) {
    int l = 1, h = p.size() - 2;
    assert(p.size() >= 3);
    while (l != h) { // collinear points are unsupported!
        int m = (l + h + 1) / 2;
        if (q.left(p[0], p[m]) >= 0) l = m;
        else h = m - 1;
    }
    ll in = min(q.left(p[0], p[1]), q.left(p.back(), p[0]));
    return min(in, q.left(p[l], p[l + 1]));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i].x >> A[i].y;
    cin >> M;
    B.resize(M);
    rep(i, M) cin >> B[i].x >> B[i].y;

    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());

    rep(j, M) if (in_convex(A, B[j]) <= 0) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
}