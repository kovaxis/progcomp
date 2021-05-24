#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> as;
    int k = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        k = max(k, a);
        as.push_back(a);
    }

    while (true) {
        int total_a = 0;
        int total_b = 0;
        for (int for_a : as) {
            total_a += for_a;
            total_b += k - for_a;
        }
        if (total_b > total_a) {
            break;
        }
        k += 1;
    }
    cout << k << endl;
}
