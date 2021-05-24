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

    int tests;
    cin >> tests;
    vector<int> arr;
    arr.reserve(50);
    for (int t = 0; t < tests; t++) {
        int n;
        cin >> n;
        arr.clear();
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            arr.push_back(a);
        }
        sort(arr.begin(), arr.end());
        int last = arr[0];
        int ok = true;
        for (int i = 0; i < n; i++) {
            if (arr[i] - last > 1) {
                ok = false;
                break;
            }
            last = arr[i];
        }
        if (ok) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
