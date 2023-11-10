// https://codeforces.com/gym/104555/problem/G
// convex hull including collinear points

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

struct P {
    ll x, y;
    int i;

    P operator-(P r) { return {x - r.x, y - r.y}; }

    P rot() const { return {-y, x}; }
    ll operator*(P r) const { return x * r.x + y * r.y; }
    ll operator%(P r) const { return rot() * r; }
    ll left(P a, P b) { return (b - a) % (*this - a); }
};

// ccw order, excludes collinear points by default
// may duplicate collinears if they are included
vector<P> chull(vector<P> p) {
    if (p.size() < 3) return p;
    vector<P> r;
    int m, k = 0;
    sort(p.begin(), p.end(), [](P a, P b) { return a.x != b.x ? a.x < b.x : a.y < b.y; });
    for (P q : p) { // lower hull
        while (k >= 2 && r[k - 1].left(r[k - 2], q) > 0)
            r.pop_back(), k--; // >= to > to add collinears
        r.push_back(q), k++;
    }
    if (k == (int)p.size()) return r;
    r.pop_back(), k--, m = k;
    for (int i = p.size() - 1; i >= 0; --i) { // upper hull
        while (k >= m + 2 && r[k - 1].left(r[k - 2], p[i]) > 0)
            r.pop_back(), k--; // >= to > to add collinears
        r.push_back(p[i]), k++;
    }
    r.pop_back();
    return r;
}

int N;
vector<P> A;

int main() {
    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i].x >> A[i].y;
    rep(i, N) A[i].i = i;

    vector<P> ch = chull(A);
    vector<int> out;
    for (P p : ch) out.push_back(p.i);
    sort(out.begin(), out.end());
    for (int i : out) cout << i + 1 << " ";
    cout << endl;
}