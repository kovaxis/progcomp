#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int m;
    cin >> m;
    for (int i = n / 2; i >= 0; i--) {
        int steps = i + (n - 2 * i);
        if (steps % m == 0) {
            cout << steps << endl;
            return 0;
        }
    }
    cout << "-1" << endl;
}
