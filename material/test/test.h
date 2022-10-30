
#ifndef TEST_H
#define TEST_H

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static mt19937 testrng(chrono::steady_clock::now().time_since_epoch().count());

template <class G, class OP>
void deftest(OP test, G tester) {
    tester(test);
}

// [lo, hi)
int random_int(int lo, int hi) {
    uniform_int_distribution<int> d(lo, hi - 1);
    return d(testrng);
}

// [lo, hi)
ll random_ll(ll lo, ll hi) {
    uniform_int_distribution<ll> d(lo, hi - 1);
    return d(testrng);
}

// [lo, hi)
float random_float(float lo, float hi) {
    uniform_real_distribution<float> d(lo, hi);
    return d(testrng);
}

// [lo, hi)
double random_double(double lo, double hi) {
    uniform_real_distribution<double> d(lo, hi);
    return d(testrng);
}

#endif