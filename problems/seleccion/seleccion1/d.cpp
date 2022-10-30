#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    char c;
    int acc = 0;
    int count = 0;
    bool cut_1 = false;
    bool cut_2 = false;
    while (cin >> c) {
        if (c < '0' || c > '9') {
            break;
        }
        int val = c - '0';
        if (val % 3 == 0) {
            acc = 0;
            cut_1 = false;
            cut_2 = false;
            count += 1;
        } else {
            acc += val;
            if (acc % 3 == 0 || (acc % 3 == 1 && cut_1) ||
                (acc % 3 == 2 && cut_2)) {
                acc = 0;
                cut_1 = false;
                cut_2 = false;
                count += 1;
            } else {
                if (acc % 3 == 1) {
                    cut_1 = true;
                } else if (acc % 3 == 2) {
                    cut_2 = true;
                }
            }
        }
    }
    cout << count << endl;
}
