#include "common.h"

// search x in a[i]
//
// first a[i] >  x:   upper_bound(a, x)
// first a[i] >= x:   lower_bound(a, x)
//  last a[i] <  x: --lower_bound(a, x)
//  last a[i] <= x: --upper_bound(a, x)

// note: searching for the largest [l, r] such that f(l) > a & f(r) < b where
// [a, b] is a range in f() space may result in negative [l, r] ranges.

// discrete binary search.
//
// searches in an integer range of the form [begin, end].
//
// returns the lowest value `m` such that `!lt(m, val)` holds true.
// this means that if `lt(m, val)` is defined as `f(m) < f(val)`, then this
// function returns the first value such that `f(m) >= f(val)`, just like
// `lower_bound`.
//
// if `lt(m, val)` is defined as `f(m) <= f(val)`, then this
// function returns the first value such that `f(m) > f(val)`, just like
// `upper_bound`.
int binsearch(int val, int l, int r, bool lt(int, int)) {
    while (l != r) {
        int m = l + (r - l) / 2;
        if (lt(m, val)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

// range binary search.
// returns the first index `k` such that `query(i, k+1)` is larger than or equal
// to `mn`. if `query` is range maximum on the range [l, r), finds the first `k
// >= i` such that `A[k] >= mn`.
template <class OP>
int rangesearch(int i, int mn, int N, OP query) {
    int l = i, r = N;
    while (l != r) {
        int m = l + (r - l) / 2;
        if (query(i, m + 1) < mn) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

// continuous binary search.
//
// the predicate replaces the `<` operator.
//
// iterates `iter` times, giving about a precision of about 2^-iter.
double cbinsearch(int iter, double val, double l, double r,
                  bool lt(double, double)) {
    for (int i = 0; i < iter; i++) {
        double mid = (l + r) / 2;
        if (lt(val, mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return (l + r) / 2;
}

// continuous ternary (golden section) search.
//
// searches for a minimum value for the given unimodal function (monotonic
// positive derivative).
template <typename T, typename U>
pair<T, U> ctersearch(int iter, T a, T b, U f(T)) {
    const T INVG = 0.61803398874989484820;

    U av = f(a);
    U bv = f(b);

    T mid = a + (b - a) * INVG;
    U midv = f(mid);

    for (int i = 0; i < iter; i++) {
        T new_mid = a + (mid - a) * INVG;
        U new_midv = f(new_mid);
        if (new_midv > midv) {
            // Search the right interval
            a = b;
            av = bv;
            b = new_mid;
            bv = new_midv;
        } else {
            // Search the left interval
            b = mid;
            bv = midv;
            mid = new_mid;
            midv = new_midv;
        }
    }
    return {mid, midv};
}

int main() {
    vector<int> ints = {4, 8, 9, 9, 11, 20};

    // lower_bound
    assert(lower_bound(ints.begin(), ints.end(), 3) - ints.begin() == 0);
    assert(lower_bound(ints.begin(), ints.end(), 9) - ints.begin() == 2);
    assert(lower_bound(ints.begin(), ints.end(), 10) - ints.begin() == 4);
    assert(lower_bound(ints.begin(), ints.end(), 25) - ints.begin() == 6);

    // upper_bound
    assert(upper_bound(ints.begin(), ints.end(), 3) - ints.begin() == 0);
    assert(upper_bound(ints.begin(), ints.end(), 9) - ints.begin() == 4);
    assert(upper_bound(ints.begin(), ints.end(), 10) - ints.begin() == 4);
    assert(upper_bound(ints.begin(), ints.end(), 25) - ints.begin() == 6);

    // cbinsearch
    // Find an approximation to sqrt(782)
    float approx = cbinsearch<float>(
        0., 100., 20, [](float& val) { return val * val > 782. ? 1 : -1; });
    assert(abs(approx - sqrt(782)) < 0.0001);
    cout << "sqrt(782) ~= " << approx << endl;
}