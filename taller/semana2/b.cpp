#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l1, r1, l2, r2;
        cin >> l1;
        cin >> r1;
        cin >> l2;
        cin >> r2;
        int a = l1;
        int b = l2;
        if (a == b) {
            if (r1 > r2) {
                a = r1;
            } else {
                b = r2;
            }
        }
        cout << a << " " << b << endl;
    }
}
