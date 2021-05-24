#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    long long y = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            y = 3 * y + 1;
        } else {
            y = 3 * y - 1;
        }
        y = y % 1000000007;
    }
    if (n % 2 == 1) {
        cout << (y - 1) << endl;
    } else {
        cout << (y + 1) << endl;
    }
}
