#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n;
    cin >> q;
    vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    for (int i = 0; i < q; i++) {
        int query;
        cin >> query;
        int start = 0;
        int end = n;
        while (end - start > 1) {
            int idx = start + (end - start - 1) / 2;
            if (query >= nums[idx]) {
                // Use the right exclusive interval
                start = idx + 1;
            } else {
                // Use the left inclusive interval
                end = idx + 1;
            }
        }
        if (start < n && nums[start] == query) {
            start += 1;
        }
        if (start > 0 && nums[start - 1] == query) {
            cout << (start - 1) << endl;
        } else {
            cout << "-1" << endl;
        }
    }
}
