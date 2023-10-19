#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct P {
    ll x, y;

    P operator+(P r) { return {x + r.x, y + r.y}; }
    P operator-(P r) { return {x - r.x, y - r.y}; }
    P operator-() { return {-x, -y}; }
    P operator*(ll r) { return {x * r, y * r}; }

    ll operator*(P r) { return x * r.x + y * r.y; }
    P perp() { return {-y, x}; }

    friend istream &operator>>(istream &s, P &r) {
        return s >> r.x >> r.y;
    }

    ll magsq() { return x * x + y * y; }

    bool operator==(P r) { return x == r.x && y == r.y; }
    bool operator!=(P r) { return !(*this == r); }
};

struct L {
    P o, d;

    friend istream &operator>>(istream &s, L &r) {
        P a, b;
        s >> a >> b;
        r.o = a;
        r.d = b - a;
        return s;
    }

    ll side(P r) {
        return (r - o).perp() * d;
    }

    ll inter(L r) { return (r.o - o).perp() * r.d; }

    bool seg_collide(L r) {
        if (d.magsq() == 0) return r.point_on_seg(o);
        if (r.d.magsq() == 0) return point_on_seg(r.o);
        ll z = d.perp() * r.d;
        if (abs(z) <= 0) {
            if (abs(side(r.o)) > 0) return false;
            ll s = (r.o - o) * d, e = s + r.d * d;
            if (s > e) swap(s, e);
            return s <= d * d && e >= 0;
        }
        ll s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return s >= 0 && s <= z && t >= 0 && t <= z;
    }

    bool point_on_seg(P r) {
        if (d.magsq() == 0) return o == r;
        if (abs(side(r)) > 0) return false;
        if ((r - o) * d < 0) return false;
        if ((r - o - d) * d > 0) return false;
        return true;
    }

    L reverse() { return {o + d, -d}; }
};

P A, B;
L C[2];

bool can_direct() {
    L direct{A, B - A};
    return !direct.seg_collide(C[0]) && !direct.seg_collide(C[1]);
}

bool try_pivot(P a, L al, P b, L bl) {
}

bool can_pivot() {
    vector<L> pivots = {C[0], C[0].reverse(), C[1], C[1].reverse()};
    rep(i, 4) rep(j, 4) {
        if (try_pivot(A, pivots[i], B, pivots[j])) return true;
    }
    return false;
}

int solve() {
    // try 0 turns
    if (can_direct()) return 0;

    // try 1 turn
    if (can_pivot()) return 1;

    // can always do with 2 turns
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> A >> B;
        rep(k, 2) cin >> C[k];

        cout << solve() << "\n";
    }
}
