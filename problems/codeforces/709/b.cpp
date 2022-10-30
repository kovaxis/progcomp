#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        int out_c = -1;
        int neg_diff = 0;
        int prev = -1;
        bool error = false;
        int max = 0;
        for (int j = 0; j < n; j++) {
            int num;
            cin >> num;
            if (num > max) {
                max = num;
            }
            if (prev != -1) {
                int diff = num - prev;
                if (diff >= 0) {
                    if (out_c < 0) {
                        out_c = diff;
                    } else {
                        if (out_c != diff) {
                            error = true;
                        }
                    }
                } else if (diff < 0) {
                    if (neg_diff >= 0) {
                        neg_diff = diff;
                    } else {
                        if (diff != neg_diff) {
                            error = true;
                        }
                    }
                }
            }
            prev = num;
        }
        if (error || (out_c == 0 && neg_diff < 0) ||
            (out_c > 0 && neg_diff < 0 && max >= out_c - neg_diff)) {
            cout << "-1" << endl;
        } else if (out_c > 0 && neg_diff < 0) {
            int out_m = out_c - neg_diff;
            cout << out_m << " " << out_c << endl;
        } else {
            cout << "0" << endl;
        }
    }
}
