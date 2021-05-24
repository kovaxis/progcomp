#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int a, b, c, r;
        cin >> a;
        cin >> b;
        cin >> c;
        cin >> r;
        if (b < a) {
            swap(a, b);
        }
        int left = max(min(c - r, b), a);
        int right = min(max(c + r, a), b);
        int mins = left - a + b - right;
        cout << mins << endl;
    }
}
