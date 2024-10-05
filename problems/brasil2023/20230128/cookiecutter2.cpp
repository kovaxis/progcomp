#include <bits/stdc++.h>
using namespace std;
typedef double ld;

const ld eps = 1e-6, pi = acos(-1.0L);
struct point {
    ld x, y;
    point(ld x = 0.0L, ld y = 0.0L) : x(x), y(y) {}
    bool operator<(const point &o) const { return x != o.x ? x < o.x : y < o.y; }
    bool operator==(const point &o) const { return abs(x - o.x) <= eps && abs(y - o.y) <= eps; }
    bool operator!=(const point &o) const { return abs(x - o.x) > eps || abs(y - o.y) > eps; }
    point operator+(const point &p) const { return {x + p.x, y + p.y}; }
    point &operator+=(const point &p) {
        x += p.x;
        y += p.y;
        return *this;
    }
    point operator-(const point &p) const { return {x - p.x, y - p.y}; }
    point &operator-=(const point &p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    point operator*(ld a) const { return {a * x, a * y}; }
    point &operator*=(ld a) {
        x *= a;
        y *= a;
        return *this;
    }
    point operator/(ld a) const { return {x / a, y / a}; }
    point &operator/=(ld a) {
        x /= a;
        y /= a;
        return *this;
    }
    ld operator*(const point &p) const { return x * p.x + y * p.y; }
    ld operator^(const point &p) const { return x * p.y - y * p.x; }
    ld angle() const { return atan2(y, x); }
    ld dist(const point &p) const { return hypot(x - p.x, y - p.y); }
    ld sqdist(const point &p) const {
        ld dx = x - p.x, dy = y - p.y;
        return dx * dx + dy * dy;
    }
    ld norm() const { return hypot(x, y); }
    point &normalize() { return *this /= norm(); }
    ld sqnorm() const { return x * x + y * y; }
    point rotate(ld a) const { return {cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y}; }
    point rotate() const {
        return {-y, x};
    }
};
point operator*(ld a, const point &p) { return {a * p.x, a * p.y}; }
point polar(ld r, ld theta) { return {r * cos(theta), r * sin(theta)}; }
istream &operator>>(istream &in, point &p) { return in >> p.x >> p.y; }
ostream &operator<<(ostream &out, const point &p) { return out << p.x << ' ' << p.y; }

int sgn(ld x) { return x > eps ? 1 : x < -eps ? -1
                                              : 0; }
struct line {
    point p, d;

    line();
    line(point p, point d) : p(p), d(d) {}
    line(point p, ld theta) : p(p), d(polar(1.0L, theta)) {}

    bool left(const point &q) const {
        return (d ^ (q - p)) >= 0.0L;
    }

    bool contain(const point &q) const {
        return abs(d ^ (q - p)) <= eps;
    }

    bool intersect(const point &a, const point &b) const {
        return sgn(d ^ (a - p)) * sgn(d ^ (b - p)) < 0;
    }

    point intersection(const line &o) const {
        ld det = d ^ o.d;
        point c = {d ^ p, o.d ^ o.p};

        return point(o.d.x * c.x - d.x * c.y, o.d.y * c.x - d.y * c.y) / det;
    }

    point intersection(const point &a, const point &b) const {
        return this->intersection(line(a, b - a));
    }
};

typedef vector<point> polygon;
polygon cut(polygon &P, line &l) {
    int N = P.size();
    polygon Q;

    for (int i = 0; i < N; ++i) {
        point &p = P[i], &p1 = P[i < N - 1 ? i + 1 : 0];
        if (l.left(p)) Q.push_back(p);
        if (l.intersect(p, p1)) Q.push_back(l.intersection(p, p1));
    }

    return Q;
}

ld area(polygon &P) {
    ld ans = 0.0;
    for (int i = 0; i < P.size() - 1; ++i)
        ans += P[i] ^ P[i + 1];
    // Si el primer punto se repite, sacar:
    ans += P.back() ^ P.front();
    return abs(ans) / 2.0L;
}

ld aux(polygon &SQ, line &l) {

    polygon C = cut(SQ, l);
    return area(C);
}

ld solve(vector<point> &P, ld N, int i0) {
    polygon SQ = {{0.0L, 0.0L}, {N, 0.0L}, {N, N}, {0.0L, N}};
    ld N2 = N * N, M = P.size();
    vector<point> C;
    point o = P[i0];

    for (int i = 0; i < i0; ++i) C.push_back(P[i]);
    for (int i = i0 + 1; i < P.size(); ++i) C.push_back(P[i]);

    sort(C.begin(), C.end(), [&](const point &p1, const point &p2) {
        point q1 = p1 - o, q2 = p2 - o;
        if (q1.y < 0.0L || (abs(q1.y) <= eps && q1.x < 0.0L)) q1 *= -1.0L;
        if (q2.y < 0.0L || (abs(q2.y) <= eps && q2.x < 0.0L)) q2 *= -1.0L;
        ld c = q1 ^ q2;
        return abs(c) > eps ? c > 0.0L : p1.x < p2.x;
    });

    int up = 0, down = 0;
    for (point &c : C) {
        if (c.y < o.y || (abs(c.y - o.y) <= eps && c.x < o.x)) ++down;
        else ++up;
    }

    ld ans = 0.0;
    for (int i = 0; i < C.size();) {
        point d = C[i] - o;
        if (d.y < 0.0L || (abs(d.y) <= eps && d.x < 0.0L)) {
            d *= -1.0L;
        }

        line L(o, d);
        ld up_A = aux(SQ, L), down_A = N2 - up_A;

        int j = i, enter_up = 0, enter_down = 0;
        while (j < C.size() && L.contain(C[j])) {
            if ((C[j] - o) * d > 0.0L) ++enter_down;
            else ++enter_up;

            ++j;
        }

        ld aux = 0.0;
        aux = max(aux, (1 + down + enter_down) / M - down_A / N2);
        aux = max(aux, (1 + up + enter_up) / M - up_A / N2);

        ans = max(ans, aux);

        down += enter_down - enter_up;
        up += enter_up - enter_down;

        i = j;
    }

    /*for(point &s : SQ) {
      point d = s-o;
      line L(o, d);

      int left = 0, right = 0;
      for(point &c : C) {
        if(L.contain(c)) {
          ++left;
          ++right;
        }
        else if(L.left(c)) {
          ++left;
        }
        else {
          ++right;
        }
      }

      ld left_A = aux(SQ, L), right_A = N2-left_A;

      ans = max(ans, (1 + left)/M - left_A/N2);
      ans = max(ans, (1 + right)/M - right_A/N2);
    }

    for(point d : {point(-o.x, o.y),
                   point(o.x-N, o.y)
                     }) {

      line L(o, d);

      int left = 0, right = 0;
      for(point &c : C) {
        if(L.contain(c)) {
          ++left;
          ++right;
        }
        else if(L.left(c)) {
          ++left;
        }
        else {
          ++right;
        }
      }

      ld left_A = aux(SQ, L), right_A = N2-left_A;

      ans = max(ans, (1 + left)/M - left_A/N2);
      ans = max(ans, (1 + right)/M - right_A/N2);

    }*/

    for (int b = 0; b < 16; ++b) {

        point d = o;
        if (b & (1 << 0)) d.x -= N;
        if (b & (1 << 1)) d.y -= N;
        if (b & (1 << 2)) d.x *= -1.0L;
        if (b & (1 << 3)) d.y *= -1.0L;

        line L(o, d);

        int left = 0, right = 0;
        for (point &c : C) {
            if (L.contain(c)) {
                ++left;
                ++right;
            } else if (L.left(c)) {
                ++left;
            } else {
                ++right;
            }
        }

        ld left_A = aux(SQ, L), right_A = N2 - left_A;

        ans = max(ans, (1 + left) / M - left_A / N2);
        ans = max(ans, (1 + right) / M - right_A / N2);
    }

    return ans;
}

void test() {
    ld N = 30;
    point o = {17.0, 9.0};

    polygon SQ = {{0.0L, 0.0L}, {N, 0.0L}, {N, N}, {0.0L, N}};

    ld _eps = 1e-5L;
    for (ld theta = 0.0; theta <= 2.0 * pi; theta += _eps) {
        line L(o, theta);
        cout << theta << ' ' << aux(SQ, L) << '\n';
    }

    cout << "----------------\n";

    /*  for(point &s : SQ) {
        point d = s-o;
        line L(o, d);

        ld a = d.angle();
        if(a < 0.0) a += 2.0*pi;
        cout << a << ' ' << aux(SQ, L) << '\n';
      }

      for(point d : {point({-o.x, o.y}),
                      point({o.x, N-o.y}),
                      point({N-o.x, o.y-N}),
                      point({o.x - N, o.y}),
                      point({0.0L, 1.0L}),
                      point({1.0L, 0.0L})}) {

        line L(o, d);

        ld a = d.angle();
        if(a < 0.0) a += 2.0*pi;
        cout << a << ' ' << aux(SQ, L) << '\n';
      }*/

    for (int b = 0; b < 16; ++b) {

        point d = o;
        if (b & (1 << 0)) d.x -= N;
        if (b & (1 << 1)) d.y -= N;
        if (b & (1 << 2)) d.x *= -1.0L;
        if (b & (1 << 3)) d.y *= -1.0L;

        line L(o, d);

        ld a = d.angle();
        if (a < 0.0) a += 2.0 * pi;
        cout << a << ' ' << aux(SQ, L) << '\n';
    }

    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(8);
    // test(); return 0;

    int N, M;
    cin >> N >> M;

    vector<point> P(M);
    for (point &p : P) cin >> p;

    ld ans = 0.0;
    for (int i = 0; i < M; ++i) {
        ld aux = solve(P, N, i);
        if (aux > ans) {
            ans = aux;
        }
    }

    cout << ans << '\n';

    return 0;
}