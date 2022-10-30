#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, p;
    cin >> n;
    cin >> p;
    int p_min = p;
    int p_max = p;
    int last = 0;
    bool first_zero = false;
    vector<int> ps_min;
    vector<int> ps_max;
    ps_min.reserve(n);
    ps_max.reserve(n);
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        if (i == 0 && t == 0) {
            first_zero = true;
        }
        if (t < last) {
            p_min -= 1;
            p_max -= 1;
        } else if (t == last && last != 0) {
            p_min -= 1;
        }
        ps_min.push_back(p_min);
        ps_max.push_back(p_max);
        last = t;
    }
    if (first_zero) {
        for (int i = 0; i < n; i++) {
            cout << "0" << endl;
        }
    } else if ((p_min == 0 && last == 0)) {
        for (int i = 0; i < n; i++) {
            cout << ps_min[i] << endl;
        }
    } else if ((p_max == 0 && last == 0) || (p_max == 1 && last != 0)) {
        for (int i = 0; i < n; i++) {
            cout << ps_max[i] << endl;
        }
    } else {
        cout << "ambiguous" << endl;
    }
}
