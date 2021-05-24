#include "2d.h"

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