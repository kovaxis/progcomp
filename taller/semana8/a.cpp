#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    if (n % 2 == 1) {
        n = 0;
    } else {
        n = 1 << (n / 2);
    }
    cout << n << endl;
}
