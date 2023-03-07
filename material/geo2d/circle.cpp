#include "line.cpp"
#include "point.cpp"

struct C {
    P o;
    T r;

    // find the circumcircle of the given **non-degenerate** triangle
    static C thru_points(P a, P b, P c) {
        P p = L((a + b) / 2, (b - a).rot()).intersection(L((a + c) / 2, (c - a).rot()));
        return {p, (p - a).mag()};
    }

    // intersects the circle with a line
    // returns the number of intersections
    // places intersection in `out`
    // needs space in `out` for at most 2 intersections
    // SEMITESTED
    int line_inter(L l, P *out) const {
        P c = l.closest_to(o);
        T c2 = (c - o).magsq();
        if (c2 > r * r) return 0;
        if (c2 == r * r) return out[0] = c, 1;
        P e = sqrt(r * r - c2) * l.d.unit();
        return out[0] = c - e, out[1] = c + e, 2;
    }

    // calculates the intersections between two circles
    // returns results the same way as `line_inter`
    // the circles must not be concentric
    // UNTESTED
    int inter(C h, P *out) const {
        L l(-2 * (o - h.o), (o - h.o).magsq() + h.r * h.r - r * r);
        return h.o = {}, h.line_inter(l, out);
    }

    // check if the given circles intersect
    bool collide(C h) const {
        return (h.o - o).magsq() <= (h.r + r) * (h.r + r);
    }

    // get the two tangent points between a circle and a point
    // the point must not be inside the circle
    // UNTESTED
    pair<P, P> tangents(P p) const {
        p = p - o;
        T c = r * r / p.magsq();
        P m = o + c * p;
        P x = sqrt(c * (1. - c)) * p.rot();
        return {m - x, m + x};
    }
};
