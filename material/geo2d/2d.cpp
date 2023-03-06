#include "../common.h"

typedef double T;

struct P {
    T x;
    T y;

    P(T x_, T y_) : x{x_}, y{y_} {}
    P() : x{0}, y{0} {}

    friend ostream &operator<<(ostream &s, const P &self) {
        s << self.x << " " << self.y;
        return s;
    }
    friend istream &operator>>(istream &s, P &self) {
        s >> self.x;
        s >> self.y;
        return s;
    }

    P &operator+=(const P &r) {
        this->x += r.x;
        this->y += r.y;
        return *this;
    }
    friend P operator+(P l, const P &r) { return {l.x + r.x, l.y + r.y}; }

    P &operator-=(const P &r) {
        this->x -= r.x;
        this->y -= r.y;
        return *this;
    }
    friend P operator-(P l, const P &r) { return {l.x - r.x, l.y - r.y}; }
    P operator-() { return {-this->x, -this->y}; }

    P &operator*=(const T &r) {
        this->x *= r;
        this->y *= r;
        return *this;
    }
    friend P operator*(P l, const T &r) { return {l.x * r, l.y * r}; }
    friend P operator*(const T &l, P r) { return {l * r.x, l * r.y}; }

    P &operator/=(const T &r) {
        this->x /= r;
        this->y /= r;
        return *this;
    }
    friend P operator/(P l, const T &r) { return {l.x / r, l.y / r}; }

    // Dot product
    friend T operator*(P l, const P &r) { return l.x * r.x + l.y * r.y; }

    // Cross product (equiv to l.perp() * r in 2D)
    friend T operator^(P l, const P &r) { return l.x * r.y - l.y * r.x; }

    T magsq() { return this->x * this->x + this->y * this->y; }
    T mag() { return sqrt(this->magsq()); }
    P unit() { return (1. / this->mag()) * (*this); }

    P perp() { return {-this->y, this->x}; }

    double angle() { return atan2((double)this->y, (double)this->x); }
    float angle_float() { return atan2((float)this->y, (float)this->x); }
    static P from_angle(T angle) { return {(T)cos(angle), (T)sin(angle)}; }
};

// receives two segments in origin/distance format.
// the second segment is extended to infinity
// returns a weight, representing how much along the first line segment do the
// lines intersect.
// if it is in the [0, 1] range, they intersect.
T seg_line(P o0, P d0, P o1, P d1) {
    T d = d0 ^ d1;
    if (d == 0) return 0;
    return ((o1 - o0) ^ d0) / d;
}

// returns true if two segments intersect.
// handles all corner cases correctly, including parallel and zero
// sized segments.
// in the non-parallel case, the intersection point can be retrieved
// as `o0 + n0 / d * d0` or `o1 + n1 / d * d1`.
bool seg_seg(P o0, P d0, P o1, P d1) {
    P o = o1 - o0;
    T d = d0 ^ d1;
    if (d == 0) {
        if ((o ^ d0) != 0) return false;
        T e0 = o * d0, e1 = (o + d1) * d0;
        return (0 <= e1 && e0 <= d0 * d0) || (0 <= e0 && e1 <= d0 * d0);
    }
    T n0 = o ^ d0, n1 = o ^ d1;
    if (d < 0) n0 = -n0, n1 = -n1, d = -d;
    return 0 <= n0 && n0 <= d && 0 <= n1 && n1 <= d;
}

// iterate over all slopes, keeping points sorted with respect to the signed
// distance to the slope.
template <class OP>
void iter_slopes(vector<P> &points, OP op) {
    int N = points.size();
    vector<pair<int, int>> slopes;
    rep(i, N) rep(j, N) {
        if (i == j) continue;
        slopes.push_back({i, j});
    }
    vector<int> perms(N);
    rep(i, N) perms[i] = i;
    sort(slopes.begin(), slopes.end(), [&](pair<int, int> i, pair<int, int> j) {
        P d1 = points[i.second] - points[i.first];
        P d2 = points[j.second] - points[j.first];
        return (d1 ^ d2) > 0;
    });
    for (auto &s : slopes) {
        int i = perms[s.first], j = perms[s.second];
        op(i, j);
        swap(points[perms[i]], points[perms[j]]);
        swap(perms[i], perms[j]);
    }
}

#ifndef NOMAIN_2D

int main() {
    vector<vector<T>> tests{
        {2, 1, -1, 4, 1, 1, 0, 2},
        {2, 1, -1, 4, 1, 1, 1, 2},
        {2, 1, -1, 4, 3, 0, 4, -1},
        {2, 1, -1, 4, 3, 0, -2, 5},
        {1, 2, 0, 1, 0, 0, 1, 1},
        {0, 0, 1, 1, -1, 1, 0, 0},
        {0, 0, 1, 1, -1, 1, 1, -1},
    };
    for (auto t : tests) {
        P v[4] = {{t[0], t[1]}, {t[2], t[3]}, {t[4], t[5]}, {t[6], t[7]}};
        bool ans = seg_intersect(v[0], v[1] - v[0], v[2], v[3] - v[2]);
        bool ans2 = seg_intersect(v[1], v[0] - v[1], v[3], v[2] - v[3]);
        if (ans2 != ans) throw "error!";
        cout << "(" << v[0] << " : " << v[1] << ") & (" << v[2] << " : " << v[3]
             << ") = " << (ans ? "YES" : "NO") << "\n";
    }
}

#endif
