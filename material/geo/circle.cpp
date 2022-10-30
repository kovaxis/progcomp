#define NOMAIN_2D
#include "2d.cpp"

struct Circle {
    Vec2 o;
    T r;
};

/// Find the pair of tangent points on circumference `c` to point `p`.
/// That is, find the tangent lines that cross point `p` and intersect the
/// circumference `c`, and return the points where these lines intersect `c`.
///
/// The first point returned is the counterclockwise tangent, followed by the
/// clockwise tangent.
///
/// If the point is inside the circle, NaN is returned.
pair<Vec2, Vec2> tangents(Circle c, Vec2 p) {
    Vec2 d = p - c.o;
    T r2d2 = c.r * c.r / d.magsq();
    Vec2 mid = c.o + r2d2 * d;
    Vec2 dif = sqrt(r2d2 * (1. - r2d2)) * d.rotated();
    return {mid + dif, mid - dif};
}

#ifndef NOMAIN_CIRCLE

int main() {
    Circle c = {{8., 10.}, 3.};
    pair<Vec2, Vec2> points = tangents(c, {-1., 1.});
    cout << points.first << ", " << points.second << endl;
}

#endif
