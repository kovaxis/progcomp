#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0L);
const double EPS = 1e-12;

// POINT 2D

typedef double T;
struct P {
    T x, y;
    P() {}
    P(T x, T y) : x(x), y(y) {}

    P operator+(const P &p) const { return P(x + p.x, y + p.y); }
    P operator-(const P &p) const { return P(x - p.x, y - p.y); }
    P operator*(const double &c) const { return P(x * c, y * c); }
    P operator/(const double &c) const { return P(x / c, y / c); }
    T operator^(const P &p) const { return x * p.y - y * p.x; }
    T operator*(const P &p) const { return x * p.x + y * p.y; }
    bool operator==(const P &p) const {
        return abs(x - p.x) + abs(y - p.y) < EPS;
    }
    bool operator<(const P &p) const {
        return abs(x - p.x) > EPS ? p.x - x > EPS : p.y - y > EPS;
    }

    T norm2() const { return x * x + y * y; }
    double norm() const { return sqrt(norm2()); }
    double ang() {
        double a = atan2(y, x);
        if (a < 0) a += 2. * PI;
        return a;
    }
    P unit() { return (*this) / norm(); }
    P perp() { return P(-y, x); }
    P rot(P r) { return P((*this) ^ r, (*this) * r); }
    P rot(double a) { return rot(P(sin(a), cos(a))); }
};
istream &operator>>(istream &s, P &p) { return s >> p.x >> p.y; }
ostream &operator<<(ostream &s, const P &p) {
    return s << '(' << p.x << ", " << p.y << ')';
}

typedef struct {
    P fish;
    double angle;
} SortFish;

bool cmp_fish(SortFish a, SortFish b) { return a.angle < b.angle; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    double radius;
    int n;
    cin >> radius;
    cin >> n;
    vector<P> fishes;
    vector<SortFish> tmp;
    for (int i = 0; i < n; i++) {
        P fish;
        cin >> fish;
        fishes.push_back(fish);
        tmp.push_back(SortFish{fish, 0.});
    }

    int max_count = 0;
    for (int i = 0; i < n; i++) {
        P &a = fishes[i];
        // cout << "bordering on fish " << a << endl;
        for (int j = 0; j < n; j++) {
            P &b = fishes[j];
            double angle = atan2(b.y - a.y, b.x - a.x);
            tmp[j] = SortFish{
                b,
                angle,
            };
        }
        sort(tmp.begin(), tmp.end(), cmp_fish);
        for (int j = 0; j < n; j++) {
            P &b = tmp[j].fish;
            // cout << "  bordering also on fish " << b << endl;
            P mid = (b - a) / 2.;
            P dir = (b - a).perp();
            if (dir.norm2() >= 10e-6) {
                dir = dir.unit();
            }
            double len = sqrt(radius * radius - mid.norm2());
            P center = a + mid + dir * len;
            // cout << "  centering on " << center << endl;
            // Count points
            int count = 0;
            for (int k = 0; k < n; k++) {
                if ((fishes[k] - center).norm() <= radius + 10e-6) {
                    // cout << "    fish " << fishes[k] << " is inside" << endl;
                    count += 1;
                }
            }
            if (count > max_count) {
                max_count = count;
            }
        }
    }
    cout << max_count << endl;
}
