#include <bits/stdc++.h>
#include <math.h>
using namespace std;

template <typename T>
T cbinsearch(T begin, T end, int precision, int predicate(T&)) {
    for (int iter = 0; iter < precision; iter++) {
        T mid = (begin + end) / 2;
        T tmp = mid;
        int heur = predicate(tmp);
        if (heur > 0) {
            end = mid;
        } else if (heur < 0) {
            begin = mid;
        } else {
            return tmp;
        }
    }
    return (begin + end) / 2;
}

double b, c;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        cin >> b;
        cin >> c;
        double x = cbinsearch<double>(0, 3.15 / 2., 30, [](double& x) {
            double cot = 1. / tan(x);
            return b + 2 * x - (c + x * (b + x)) * cot > 0. ? 1 : -1;
        });
        double y = (x * x + b * x + c) / sin(x);
        cout << fixed << setw(10) << setprecision(10) << y << endl;
    }
}
