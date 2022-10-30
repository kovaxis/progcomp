#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string s;
    string t;
    cin >> n;
    cin >> s;
    cin >> t;

    vector<int> moves;
    for (int i = 0; i < n; i++) {
        int at_s = -1;
        for (int j = i; j < n; j++) {
            if (s[j] == t[i]) {
                // Get this char
                at_s = j;
                break;
            }
        }
        if (at_s == -1) {
            cout << "-1" << endl;
            return 0;
        }
        for (int j = i; j < at_s; j++) {
            moves.push_back(j);
        }
        s[at_s] = s[i];
        for (int j = at_s - 2; j >= i; j--) {
            moves.push_back(j);
        }
        // s[i] = t[i];
    }
    cout << moves.size() << endl;
    bool first = true;
    for (int m : moves) {
        if (!first) {
            cout << " ";
        }
        first = false;
        cout << (m + 1);
    }
    cout << endl;
}
