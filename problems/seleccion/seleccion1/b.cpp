#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        s.clear();
        cin >> s;
        char cmp_char = s[0];
        int good_idx = -1;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != cmp_char) {
                good_idx = i;
                break;
            }
        }
        if (good_idx == -1) {
            cout << "-1" << endl;
        } else {
            for (int i = 0; i < s.size(); i++) {
                if (i != good_idx) {
                    cout << s[i];
                }
            }
            cout << s[good_idx] << endl;
        }
    }
}
