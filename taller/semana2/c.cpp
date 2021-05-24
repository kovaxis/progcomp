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

    int t_count;
    cin >> t_count;
    vector<int> poly;
    vector<int> out;
    poly.reserve(256);
    out.reserve(256);
    for (int t = 0; t < t_count; t++) {
        int deg_a_tmp;
        int deg_a = 0;
        poly.clear();
        cin >> deg_a_tmp;
        for (int i = 0; i <= deg_a_tmp; i++) {
            int coef;
            cin >> coef;
            poly.push_back(coef);
            if (coef != 0) {
                deg_a = i;
            }
        }
        int deg_b = 0;
        int deg_b_tmp;
        cin >> deg_b_tmp;
        out.clear();
        for (int i = 0; i <= deg_a + deg_b_tmp; i++) {
            out.push_back(0);
        }
        for (int i = 0; i <= deg_b_tmp; i++) {
            int coef;
            cin >> coef;
            if (coef != 0) {
                deg_b = i;
            }
            for (int j = 0; j <= deg_a; j++) {
                out[i + j] += poly[j] * coef;
            }
        }
        cout << (deg_a + deg_b) << endl;
        for (int i = 0; i <= deg_a + deg_b; i++) {
            if (i > 0) {
                cout << " ";
            }
            cout << out[i];
        }
        cout << endl;
    }
}
