#include "math.h"

int main() {
    // Floor division
    assert(floordiv(3, 5) == 0);
    assert(floordiv(7, 5) == 1);
    assert(floordiv(-2, 5) == -1);
    assert(floordiv(-7, 3) == -3);
    assert(floordiv(-6, 3) == -2);
    assert(floordiv(-0, 7) == 0);
    assert(floordiv(2, -5) == -1);
    assert(floordiv(7, -3) == -3);
    assert(floordiv(6, -3) == -2);
    assert(floordiv(0, -7) == 0);

    // Count divisors
    assert(count_divisors(1) == 1);
    assert(count_divisors(2) == 2);
    assert(count_divisors(3) == 2);
    assert(count_divisors(4) == 3);
    assert(count_divisors(5) == 2);
    assert(count_divisors(6) == 4);
    assert(count_divisors(7) == 2);
    assert(count_divisors(16) == 5);
    assert(count_divisors(42) == 8);
    assert(count_divisors(101) == 2);
}