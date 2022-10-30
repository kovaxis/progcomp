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
            int idx = start + (end - start) / 2;
            if (query > nums[idx]) {
                // Use the right inclusive interval
                start = idx;
            } else {
                // Use the left exclusive interval
                end = idx;
            }
        }
        if (end > 0 && nums[end - 1] == query) {
            end -= 1;
        }
        if (end < n && nums[end] == query) {
            cout << end << endl;
        } else {
            cout << "-1" << endl;
        }
    }
}
