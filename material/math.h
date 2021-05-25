#include <bits/stdc++.h>
using namespace std;

inline int floordiv(int a, int b) {
    int d = a / b;
    return d * b == a ? d : d - ((a < 0) ^ (b < 0));
}

// Counts the divisors of a positive integer.
int count_divisors(int x) {
    int divs = 1;
    int i = 2;
    while (x > 1) {
        if (i * i > x) {
            divs *= 2;
            break;
        }
        int n = 1;
        while (x % i == 0) {
            x /= i;
            n += 1;
        }
        divs *= n;
        i += 1;
    }
    return divs;
}
