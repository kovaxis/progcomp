#include <bits/stdc++.h>
using namespace std;

// Discrete binary search.
//
// Searches in an integer range of the form [begin, end).
int binsearch(int val, int begin, int end, bool lt(int, int)) {
    while (end > begin) {
        int mid = begin + (end - begin) / 2;
        if (lt(val, mid)) {
            end = mid;
        } else {
            begin = mid + 1;
        }
    }
    return begin;
}

// Continuous binary search.
//
// The predicate replaces the `<` operator.
//
// Iterates `precision` times.
double cbinsearch(int precision, double val, double begin, double end,
                  bool lt(double, double)) {
    for (int iter = 0; iter < precision; iter++) {
        double mid = (begin + end) / 2;
        if (lt(val, mid)) {
            end = mid;
        } else {
            begin = mid;
        }
    }
    return (begin + end) / 2;
}

// Continuous ternary (golden section) search.
//
// Searches for a minimum value for the given unimodal function (monotonic
// positive derivative).
template <typename T, typename U>
pair<T, U> ctersearch(int precision, T a, T b, U f(T)) {
    const T INVG = 0.61803398874989484820;

    U av = f(a);
    U bv = f(b);

    T mid = a + (b - a) * INVG;
    U midv = f(mid);

    for (int iter = 0; iter < precision; iter++) {
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
